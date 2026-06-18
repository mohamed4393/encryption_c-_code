#ifndef BLACK_HOLE_HASH_HPP
#define BLACK_HOLE_HASH_HPP

#include <cstdint>
#include <bit>
//بسم الله الرحمن الرحيم 
//i dont know how to discripe or make understand that code
namespace hbh {


    inline unsigned char cutter(uint32_t value){
        return (value & 0xFF) ^ ((value >> 8) & 0xFF) ^ ((value >> 16) & 0xFF) ^ ((value >> 24) & 0xFF);
    }


    inline uint32_t I(uint32_t a,uint32_t b,uint32_t c,uint32_t d){
        uint8_t a_1 = (a & 0xFF);uint8_t b_1 = ((b >> 8) & 0xFF);
        uint8_t c_1 = ((c >> 16) & 0xFF);uint8_t d_1 = ((d >> 24) & 0xFF);
        return (std::rotr(a_1,cutter(b)))^ static_cast<uint32_t>((std::rotl(b_1,cutter(c))) << 8) ^ static_cast<uint32_t>((static_cast<unsigned char>(c_1 + d))  << 16) ^ static_cast<uint32_t>((static_cast<unsigned char>(d_1 - a)) << 24);
    }

    inline void G(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t m0, uint32_t m1){
        uint8_t cases[] = {1,2,3,4,5,6,7,8};
        for (uint8_t i = 0; i < 8; i++)
        {
            std::swap(cases[i],cases[(hanfozlik(d, i, b, c))&7]);
        }
        for (uint8_t i = 0; i < 8; i++)
        {
            switch (cases[i])
            {
                case 1:
                a = a + b + m0;
                break;
                case 2:
                a =std::rotl(a,b + (b ^ (a + c)));
                break;
                case 3:
                b = a + m1;
                break;
                case 4:
                b =std::rotl(b,a + (a ^ (d + c)));
                break;
                case 5:
                d = c + (m1 ^ m0);
                break;
                case 6:
                d =std::rotl(d,a + (a ^ (d + b)));
                break;
                case 7:
                c = (a & b) ^ (c & b) ^ (b & d)^ (~a & d);
                break;
                case 8:
                c =std::rotl(c,d + (d ^ (a + a)));
                break;
            }
        }
    }
    inline uint32_t hanfozlik(uint32_t a,uint32_t b,uint32_t c,uint32_t d){
        uint8_t cases[] = {0,1,2,3,4,5,6,7};
        for (uint8_t i = 0; i < 8; i++)
        {
            std::swap(cases[i],cases[(potato(d, i, b, c,a+(b==0)+b))&7]);
        }
        for (uint8_t i = 0; i < 8; i++)
        {
            switch (cases[i])
            {
                case 0:
                a = ((~a) * (~a)) + (((~a) * (~a)) == 0);
                break;
                case 1:
                b = b = ((~b) * (~b)) + (((~b) * (~b)) == 0);
                break;
                case 2:
                c = c = ((~c) * (~c)) + (((~c) * (~c)) == 0);
                break;
                case 3:
                d = ((~d) * (~d)) + (((~d) * (~d)) == 0);
                break;
                case 4:
                a ^= std::rotl(a,b & 31) + std::rotl(a,c & 31) + std::rotl(a,d & 31);
                break;
                case 5:
                b ^= std::rotl(b,a & 31) + std::rotl(b,c & 31) + std::rotl(b,d & 31);
                break;
                case 6:
                c ^= std::rotl(c,b & 31) + std::rotl(c,a & 31) + std::rotl(c,d & 31);
                break;
                case 7:
                d ^= std::rotl(d,b & 31) + std::rotl(d,c & 31) + std::rotl(d,a & 31);
                break;
            }
        }
        return (a ^ ((b + c) ^ d)) + 
        ((a - (b ^ c)) + d) - 
        (std::rotr(a,b & 31) + std::rotl(c,d & 31)) + 
        (std::rotl(std::rotr(a,(c ^ b)& 31),std::rotl(b,(d ^ a)& 31)) - std::rotr(std::rotr(d,(b ^ d)& 31),std::rotl(c,(b ^ c)& 31)));
    }

    inline uint32_t potato(uint32_t x,uint32_t y ,uint32_t z,uint32_t world_size_x,uint32_t world_size_z){
        uint32_t mask_z = z + (world_size_z ^ y);
        uint32_t mask_x = x + (world_size_x ^ mask_z);
        return std::rotl(mask_x,mask_z & 0x1F);
    }
    inline uint32_t T(uint32_t y,uint32_t z,uint32_t x){
        uint32_t k = (x & y) ^ (x & z) ^ (y & z)^ (~x & z)^ (std::rotl(x,((~x & z) & 31)));
        uint32_t p = k + (~k ^ std::rotl(k,~k & 31  - ((x & y) ^ (x & z) ^ (y & z)^ (~x & z))));
        uint32_t c = ((((p >> 24) & 0xFF) + ((p >> 16) & 0xFF)) ^ ((p >> 8)  & 0xFF)) + p;
        c += (c * c) | ((c - p) | 1);
        return std::rotl(p + c, 7) ^ std::rotr(p - c, 11);
    }

    inline uint32_t final(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t m0, uint32_t m1){
        uint32_t result = 0;
        uint8_t Zero_killers[] = {0,1,2,3};
        uint8_t lines[] = {0,1,2,3};
        for (uint8_t i = 0; i < 4; i++)
        {
            std::swap(lines[i],lines[(hanfozlik(d, i, b, c))&3]);
            std::swap(Zero_killers[i],Zero_killers[(hanfozlik(d, i, b, c))&3]);
        }

        for (uint8_t i = 0; i < 4; i++)
        {
            switch (Zero_killers[i])
            {
            case 0:
                a = hanfozlik(d, a, b, c);
                break;
            case 1:
                b = hanfozlik(d,b,a,c);
                break;
            case 2:
                c = hanfozlik(a,d,b,c);
                break;
            case 3:
                d = hanfozlik(a,b,c,d);
                break;
            }
        }
        for (uint8_t i = 0; i < 4; i++)
        {
            switch (lines[i])
            {
            case 0:
                result = T(a,b,c + d);
                break;
            case 1:
                result = potato(a,b,c,d,result);
                break;
            case 2:
                result = I(a,b,c,result);
                break;
            case 3:
                G(a,b,c,d,m0,m1);
                break;
            }
        }
        return result;
    }
}

#endif