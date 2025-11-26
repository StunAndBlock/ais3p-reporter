#include "internal/Data/Meta.hpp"

#include <iostream>

error Meta::open(std::filesystem::path metaFN){
    fd_.open(metaFN, std::ios::in | std::ios::binary);
    if (!fd_.is_open()){
        std::cout << std::strerror(errno);
        return error(Status::FORCE_FIRST_START,std::strerror(errno));
        
    }
    return error::null;
}

error Meta::createFresh(std::filesystem::path metaFN){
    fd_.open(metaFN, std::ios::out | std::ios::binary);
    if (!fd_.is_open()){
        return error(std::strerror(errno));
    }

    fd_.write("nn", 2);
    return error::null;
}

error Meta::load(){
    return error::null;
}