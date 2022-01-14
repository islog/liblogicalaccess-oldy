#include <string>
#include <memory>
#include <logicalaccess/readerproviders/readerprovider.hpp>
#include <logicalaccess/plugins/readers/idondemand/idondemandreaderprovider.hpp>

extern "C" {
LLA_READERS_IDONDEMAND_API char *getLibraryName()
{
    return (char *)"IdOnDemand";
}

LLA_READERS_IDONDEMAND_API void
getIdOnDemandReader(std::shared_ptr<logicalaccess::ReaderProvider> *rp)
{
    if (rp != nullptr)
    {
        *rp = logicalaccess::IdOnDemandReaderProvider::getSingletonInstance();
    }
}

LLA_READERS_IDONDEMAND_API bool getReaderInfoAt(unsigned int index, char *readername,
                                                size_t readernamelen, void **getterfct)
{
    bool ret = false;
    if (readername != nullptr && readernamelen == PLUGINOBJECT_MAXLEN &&
        getterfct != nullptr)
    {
        switch (index)
        {
        case 0:
        {
            *getterfct = (void *)&getIdOnDemandReader;
            sprintf(readername, READER_IDONDEMAND);
            ret = true;
        }
        break;
        default:;
        }
    }

    return ret;
}
}