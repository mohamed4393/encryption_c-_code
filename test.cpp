#include <iostream>
#include <cstdint>
#include <bit>
#include <array>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <span>

inline uint32_t potato(uint32_t width,uint32_t x,uint32_t y,size_t offest){return offest+(((x*width)+y)*3);}
int main(){
    uint32_t hight =426;
    uint32_t width =640;
    size_t offset = 54;
    std::string file_name = "/home/mohamed/Downloads/sample_640×426.bmp";

    boost::interprocess::file_mapping m_file(file_name.c_str(),boost::interprocess::read_write);
    boost::interprocess::mapped_region region(m_file,boost::interprocess::read_write);
    std::span<uint8_t> file_matrix(static_cast<uint8_t*>(region.get_address()),region.get_size());

    for (size_t y = 0; y < hight; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            uint32_t index = potato(width,y,x,offset);
            file_matrix[index] = 0;
            file_matrix[index+1] = 0;
            file_matrix[index+2] = 0;
        }
        
    }
    region.flush();
    


    return 0;}