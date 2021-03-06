#include "Kerberos.h"

namespace kerberos
{
    void Kerberos::bootstrap(const std::string & configuration)
    {
        // ---------------------
        // Initialize kerberos

        configure(configuration);

        // ------------------------------------------
        // Guard is a filewatcher, that looks if the 
        // configuration has been changed. On change 
        // guard will re-configure all instances.

        std::string directory = configuration.substr(0, configuration.rfind('/'));
        std::string file = configuration.substr(configuration.rfind('/')+1);
        guard = new FW::Guard();
        guard->listenTo(directory, file);
        
        guard->onChange(&Kerberos::reconfigure);
        guard->start();
        
        // --------------------------
        // This should be forever...

        while(true)
        {
            // -------------------
            // Initialize data

            JSON m_data;
            m_data.SetObject();


            // ------------------------------------
            // Guard look if the configuration has
            // been changed...
            
            guard->look();
            
            // --------------------------------------------
            // If machinery is NOT allowed to do detection
            // continue iteration
            
            if(!machinery->allowed(images))
            {
                continue;
            }
            
            // --------------------
            // Clean image to save

            Image cleanImage = *images[images.size()-1];

            // --------------
            // Processing..
            
            if(machinery->detect(images, m_data))
            {
                machinery->save(cleanImage, m_data);
            }

            // -------------
            // Shift images
            
            images = capture->shiftImage();
        }
    }

    void Kerberos::configure(const std::string & configuration)
    {
        // ---------------------------
    	// Get settings from XML file

        StringMap settings = kerberos::helper::getSettingsFromXML(configuration);
        
        // ---------------------------
        // Initialize capture device
        
        if(capture != 0)
        {
            capture->close();
            delete capture;
        }
        capture = Factory<Capture>::getInstance()->create(settings.at("capture"));
        capture->setup(settings);

        // -------------------
        // Take first images

        for(ImageVector::iterator it = images.begin(); it != images.end(); it++)
        {
            delete *it;
        }

        images.clear();
        images = capture->takeImages(3);
        
        // --------------------
        // Initialize machinery

        if(machinery != 0) delete machinery;
        machinery = new Machinery();
        machinery->setup(settings);
        machinery->initialize(images);
    }
}