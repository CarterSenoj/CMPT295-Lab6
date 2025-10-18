#include <stdint.h>
#include <stdio.h>
#include "utf8.h"

/* UTF8 encoding reminder
    1 byte: 0xxxxxxx
    2 byte: 110xxxxx 10xxxxxx
    3 byte: 1110xxxx 10xxxxxx 10xxxxxx
    4 byte: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    10xxxxxx marks a continuation byte
*/

void decode_utf8(const char* s) {
    size_t i = 0;
    while (s[i] != '\0') {
        // cast to 8 bit value for the first byte of the array
        uint8_t first_byte = (uint8_t)s[i];
        
        // single byte check
        // does first byte start with 0
        if ((first_byte & 0b10000000) == 0) {
            // get char number
            uint32_t char_num = first_byte & 0b01111111;
            // report 1 byte char found and incremennt 1 byte
            report_character(char_num, 1);
            i += 1;
        }
        // 2 byte case
        // so check for 0b11000000 by using the and trick aka masking
        // from part 2 of the lab
        else if ((first_byte & 0b11100000) == 0b11000000) {
            uint32_t char_num = 0;
            // get the 5 bits from first byte
            // then shift the bits over by 6 so that we have 
            // room to fit the next 6 bits from the byte 2
            char_num |= (first_byte & 0b00011111) << 6;
            // get the 6 bits from second byte
            // by adding 1 to i casted to a 8 bit uint
            // just like first_byte
            char_num |= ((uint8_t)s[i+1] & 0b00111111);
            // report 2 byte found and shift over 2 bytes in the array
            report_character(char_num, 2);
            i += 2;
        } 
        // 3 byte case 
        else if ((first_byte & 0b11110000) == 0b11100000) {
            uint32_t char_num = 0;
            // get the 4 bits from first byte 
            // (yes its just like the last part but 1 less bit to read
            // so and it with 1 less 1)
            // now we know we need to move these bits over 12 bits
            // to fit the 2 following bytes
            char_num |= (first_byte & 0b00001111) << 12;
            // get the 6 bits from second byte
            // shift 6 to make room for last byte
            char_num |= ((uint8_t)s[i+1] & 0b00111111) << 6;    
            // get the 6 bits from third byte
            char_num |= ((uint8_t)s[i+2] & 0b00111111);
            // report 3 bytes found and shift array 3 bytes
            report_character(char_num, 3);
            i += 3;
        }
        // 4 byte case
        else if ((first_byte & 0b11111000) == 0b11110000) {
            uint32_t char_num = 0;
            // get the 3 bits from first byte
            // shifting by 18 bits because we now know 
            // that following byte 1 will be 3 more continuation
            // bytes
            char_num |= (first_byte & 0b00000111) << 18;
            // get the 6 bits from second byte
            // shift 12 to fit 2 remaining bytes
            char_num |= ((uint8_t)s[i+1] & 0b00111111) << 12;
            // get the 6 bits from third byte
            // shift 6 to fit the remaining byte
            char_num |= ((uint8_t)s[i+2] & 0b00111111) << 6;
            // get the 6 bits from fourth byte
            // get the final continnuation byte
            char_num |= ((uint8_t)s[i+3] & 0b00111111);
            // report 4 bytes found and shift array 4 bytes
            report_character(char_num, 4);
            i += 4;
        }
    }
}