/** 
 * \file ResourceFileFactory.h
 * \brief 
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */

#ifndef RESOURCE_FILE_FACTORY_H
#define	RESOURCE_FILE_FACTORY_H

#include <map>
#include <string>



namespace nut
{

class IResourceFile;
typedef IResourceFile* (*CreateResourceFileFunc)(const std::string& path);

class ResourceFileFactory
{
    public:

    static ResourceFileFactory& getInstance()
    {
        static ResourceFileFactory instance;
        return instance;
    }

    void registerResourceFile(const std::string& id, CreateResourceFileFunc create)
    {
        m_resourceFiles[id] = create;
    }

    IResourceFile* createResourceFile(const std::string& path);


    private:

    ResourceFileFactory();

    // Stop the compiler generating methods of copy the object
    ResourceFileFactory(const ResourceFileFactory& copy) = delete;
    ResourceFileFactory& operator=(const ResourceFileFactory& copy) = delete;

    std::map< std::string, CreateResourceFileFunc > m_resourceFiles;
};

}
#endif	// RESOURCE_FILE_FACTORY_H
