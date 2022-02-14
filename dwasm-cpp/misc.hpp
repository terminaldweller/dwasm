
/**********************************************************************************************************************/
/*first line intentionally left blank.*/
/*wasm interpreter*/
/*Copyright (C) 2018 Farzad Sadeghi

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 3
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
USA.*/
/**********************************************************************************************************************/
#include <cstddef>
#include <vector>
/**********************************************************************************************************************/
int read_header(std::ifstream &wasm) {
  char head[4];
  wasm.read(head, sizeof(uint32_t));
  std::cout << head[0] << head[1] << head[2] << head[3] << "\n";
  wasm.read(head, sizeof(uint32_t));
  std::cout << (int)(head[0]) << (int)(head[1]) << (int)(head[2])
            << (int)(head[3]) << "\n";
  return 0;
}

int dump_file(std::ifstream &wasm) {
  while (wasm) {
    std::ios::pos_type before = wasm.tellg();
    uint8_t x;
    wasm >> x;
    std::ios::pos_type after = wasm.tellg();
    std::cout << std::hex << static_cast<int>(x) << "\n";
  }
  return 0;
}

int leb128_u_d(std::vector<unsigned char> in) {}
int leb128_s_d(std::vector<unsigned char> in) {}
std::vector<unsigned char> leb128_u_e() {}
std::vector<unsigned char> leb128_s_e() {}
/**********************************************************************************************************************/
/*last line intentionally left blank.*/
