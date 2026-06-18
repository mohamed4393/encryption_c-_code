#include <iostream>
#include <vector>
#include <cstdint>
#include <bit>
#include <array>
#include <algorithm>
#include <utility>
#include <string_view>
#include <numeric>
#include <charconv>
#include "مكتبات/black_hole_hash.hpp"

//~ ^ % & 
//بسم الله الرحمن الرحيم
void map_gen(std::array<uint8_t, 256> &letter_map, uint32_t &key)
{
    std::iota(letter_map.begin(), letter_map.end(), 1);
    for (int i = 0; i < 256; i++)
    {
        std::swap(letter_map[i], letter_map[(((~i) * (~i)) + (((~i) * (~i)) == 0) + (i-- < (i * (i + key)))) & 255]);
    }
}

void key_gen(std::array<uint32_t, 16> &letter_key, std::string_view &letter_point)
{
    std::iota(letter_key.begin(), letter_key.end(), 1);
    std::reverse(letter_key.begin(), letter_key.end());
    std::transform(letter_key.begin(), letter_key.end(), letter_key.begin(), [letter_point](uint32_t val) {
        return hbh::final(val,val,val,val,~(letter_point.size()),val ^ letter_point.size());
    });
    for (uint8_t i = 0; i < 16; i++)
    {
        std::swap(letter_key[i],letter_key[(((~i) * (~i)) + (((~i) * (~i)) == 0) + (i-- < (i * (i + letter_point[(i * i) % letter_point.size()]))))&15]);
    }
}

void state_gen(std::array<uint32_t, 16> &letter_states, std::string_view &letter_point){
    std::iota(letter_states.begin(), letter_states.end(), 1);
    std::reverse(letter_states.begin(), letter_states.end());
    for (uint8_t i = 0; i < 16; i++)
    {
        std::swap(letter_states[i],letter_states[(((~i) * (~i)) + (((~i) * (~i)) == 0) + (i-- < (i * (i + letter_point[(i * i) % letter_point.size()]))))&15]);
    }
    std::transform(letter_states.begin(), letter_states.end(), letter_states.begin(), [letter_point](uint32_t val) {
        return hbh::final(val,val,val,val,~(letter_point.size()),val ^ letter_point.size());
    });
}

std::vector<uint8_t> letter_lock(std::string letter, std::string key)
{
    std::string_view letter_point = letter;
    std::vector<uint8_t> letter_result(letter_point.size());
    std::array<uint8_t, 256> letter_map;
    std::array<uint32_t, 16> letter_keys, letter_states;
    uint32_t start_point = (std::transform_reduce(letter_keys.begin(),letter_keys.end(),letter_states.begin(),0) % letter_point.size());
    for (uint32_t i = 0; i < letter_point.size() - start_point; i++)
    {
        uint32_t pos = i + start_point;
        letter_result[pos] = letter_map[letter_point[pos]];
        letter_result[pos] ^= hbh::cutter(hbh::final(letter_keys[pos&15],letter_states[pos&15],pos,start_point,letter_keys[pos&15]^letter_states[pos&15],letter_keys[pos&15]^pos));
        letter_keys[pos&15] ^= letter_result[pos] ^ letter_states[pos&15] ^ letter_keys[pos&15];
        letter_states[pos&15] ^= letter_result[pos] ^ letter_states[pos&15] ^ letter_keys[pos&15];
        std::swap(letter_map[(pos^letter_result[pos]) &255],letter_map[(pos^letter_result[pos]) &255]);
    }
    for (uint32_t i = 0; i < start_point; i++)
    {
        uint32_t pos = i;
        letter_result[pos] = letter_map[letter_point[pos]];
        letter_result[pos] ^= hbh::cutter(hbh::final(letter_keys[pos&15],letter_states[pos&15],pos,start_point,letter_keys[pos&15]^letter_states[pos&15],letter_keys[pos&15]^pos));
        letter_keys[pos&15] ^= letter_result[pos] ^ letter_states[pos&15] ^ letter_keys[pos&15];
        letter_states[pos&15] ^= letter_result[pos] ^ letter_states[pos&15] ^ letter_keys[pos&15];
        std::swap(letter_map[(pos^letter_result[pos]) &255],letter_map[(pos^letter_result[pos]) &255]);
    }
    return letter_result;
}

int main()
{

    return 0;
}
