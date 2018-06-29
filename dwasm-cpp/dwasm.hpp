
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
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.*/
/**********************************************************************************************************************/
#include <map>
#include <vector>

#ifndef _WASM_HPP
#define _WASM_HPP
#define MAGIC_NUMBER 0x6d736100
#define PAGE_SIZE 65536
class enum section_id_t {custom, type, import, function, table, memory, global, export, start, element, code, data, unknown};
class enum relocation_type_t {R_WEBASSEMBLY_FUNCTION_INDEX_LEB, R_WEBASSEMBLY_TABLE_INDEX_SLEB, 
  R_WEBASSEMBLY_TABLE_INDEX_I32, R_WEBASSEMBLY_MEMORY_ADDR_LEB, R_WEBASSEMBLY_MEMORY_ADDR_SLEB, 
  R_WEBASSEMBLY_MEMORY_ADDR_I32, R_WEBASSEMBLY_TYPE_INDEX_LEB, R_WEBASSEMBLY_GLOBAL_INDEX_LEB, 
  R_WEBASSEMPLY_FUNCTION_OFFSET_I32, R_WEBASSEMBLY_SECTION_OFFSET_I32};
class enum linking_subsection_t {WASM_SEGMENT_INFO, WASM_INIT_FUNCS, WASM_COMDAT_INFO, WASM_SYMBOL_TABLE};
class enum syminfo_kind_t {SYMTAB_FUNCTION, SYMTAB_DATA, SYMTAB_GLOBAL, SYMTAB_SECTION};
class enum w_type_t {uint8, uint16, uint32, uint64, 
  varuint1, varuint7, varuint32, varuint64, varint1, 
  varint7, varint32, varint64, floatt, doublet};
struct wasm_op_t {
  wasm_op_t(std::string _mnemonic, bool _has_opnd, std::vector<w_type_t> _opnd_types) {
    mnemonic = _mnemonic;
    has_opnd = _has_opnd;
    std::for_each{_opnd_types.begin(), _opnd_types.end(), [](w_type_t __t){opnd_types.push_back(__t);}};
  }
  std::string mnemonic;
  bool has_opnd;
  std::vector<w_type_t> opnd_types;
};

std::map<uint8_t, wasm_op_t> wasm_opcodes = {
  //{0x7f, wasm_op_t{"i32", false, {}}},
  //{0x7e, wasm_op_t{"i64", false, {}}},
  //{0x7d, wasm_op_t{"f32", false, {}}},
  //{0x7c, wasm_op_t{"f64", false, {}}}, 
  //{0x7b, wasm_op_t{"anyfunc", false, {}}},
  //{0x60, wasm_op_t{"func", false, {}}},
  //{0x40, wasm_op_t{"empty_block_type", false, {}}},
  {0x00, wasm_op_t{"unreachable", false, {}}},
  {0x01, wasm_op_t{"nop", false, {}}},
  {0x02, wasm_op_t{"block", true, {w_type_t.varuint7}}},
  {0x03, wasm_op_t{"loop", true, {w_type_t.varuint7}}},
  {0x04, wasm_op_t{"if", true, {w_type_t.varuint7}}},
  {0x05, wasm_op_t{"else", false, {}}},
  {0x0b, wasm_op_t{"end", false, {}}},
  {0x0c, wasm_op_t{"br", true, {w_type_t.varuint32}}},
  {0x0d, wasm_op_t{"br_if", true, {w_type_t.varuint32}}},
  {0x0e, wasm_op_t{"br_table", true, {w_type_t.varuint32, w_type_t.varuint32, w_type_t.varuint32}}},
  {0x0f, wasm_op_t{"return", false, {}}},
  {0x10, wasm_op_t{"call", true, {w_type_t.varuint32}}},
  {0x11, wasm_op_t{"call_indirect", true, {w_type_t.varuint32, w_type_t.varuint1}}},
  {0x1a, wasm_op_t{"drop", false, {}}},
  {0x1b, wasm_op_t{"select", false, {}}},
  {0x20, wasm_op_t{"get_local", true, {w_type_t.varuint32}}},
  {0x21, wasm_op_t{"set_local", true, {w_type_t.varuint32}}},
  {0x22, wasm_op_t{"tee_local", true, {w_type_t.varuint32}}},
  {0x23, wasm_op_t{"get_global", true, {w_type_t.varuint32}}},
  {0x24, wasm_op_t{"set_global", true, {w_type_t.varuint32}}},
  {0x28, wasm_op_t{"i32.load", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x29, wasm_op_t{"i64.load", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x2a, wasm_op_t{"f32.load", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x2b, wasm_op_t{"f64.load", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x2c, wasm_op_t{"i32.load8_s", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x2d, wasm_op_t{"i32.load8_u", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x2e, wasm_op_t{"i32.load16_s", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x2f, wasm_op_t{"i32.load16_u", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x30, wasm_op_t{"i64.load8_s", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x31, wasm_op_t{"i64.load8_u", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x32, wasm_op_t{"i64.load16_s", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x33, wasm_op_t{"i64.load16_u", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x34, wasm_op_t{"i64.load32_s", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x35, wasm_op_t{"i64.load32_u", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x36, wasm_op_t{"i32.store", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x37, wasm_op_t{"i64.store", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x38, wasm_op_t{"f32.store", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x39, wasm_op_t{"f64.store", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x3a, wasm_op_t{"i32.store8", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x3b, wasm_op_t{"i32.store16", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x3c, wasm_op_t{"i64.store8", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x3d, wasm_op_t{"i64.store16", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x3e, wasm_op_t{"i64.store32", true, {w_type_t.varuint32, w_type_t.varuint32}}},
  {0x3f, wasm_op_t{"current_memory", true, {w_type_t.varuint1}}},
  {0x40, wasm_op_t{"grow_memory", true, {w_type_t.varuint1}}},
  {0x41, wasm_op_t{"i32.const", true, {w_type_t.varint32}}},
  {0x42, wasm_op_t{"i64.const", true, {w_type_t.varint64}}},
  {0x43, wasm_op_t{"f32.const", true, {w_type_t.uint32}}},
  {0x44, wasm_op_t{"f64.const", true, {w_type_t.uint64}}},
  {0x45, wasm_op_t{"i32.eqz", false, {}}},
  {0x46, wasm_op_t{"i32.eq", false, {}}},
  {0x47, wasm_op_t{"i32.ne", false, {}}},
  {0x48, wasm_op_t{"i32.lt_s", false, {}}},
  {0x49, wasm_op_t{"i32.lt_u", false, {}}},
  {0x4a, wasm_op_t{"i32.gt_s", false, {}}},
  {0x4b, wasm_op_t{"i32.gt_u", false, {}}},
  {0x4c, wasm_op_t{"i32.le_s", false, {}}},
  {0x4d, wasm_op_t{"i32.le_u", false, {}}},
  {0x4e, wasm_op_t{"i32.ge_s", false, {}}},
  {0x4f, wasm_op_t{"i32.ge_u", false, {}}},
  {0x50, wasm_op_t{"i64.eqz", false, {}}},
  {0x51, wasm_op_t{"i64.eq", false, {}}},
  {0x52, wasm_op_t{"i64.ne", false, {}}},
  {0x53, wasm_op_t{"i64.lt_s", false, {}}},
  {0x54, wasm_op_t{"i64.lt_u", false, {}}},
  {0x55, wasm_op_t{"i64.gt_s", false, {}}},
  {0x56, wasm_op_t{"i64.gt_u", false, {}}},
  {0x57, wasm_op_t{"i64.le_s", false, {}}},
  {0x58, wasm_op_t{"i64.le_u", false, {}}},
  {0x59, wasm_op_t{"i64.ge_s", false, {}}},
  {0x5a, wasm_op_t{"i64.ge_u", false, {}}},
  {0x5b, wasm_op_t{"f32.eq", false, {}}},
  {0x5c, wasm_op_t{"f32.ne", false, {}}},
  {0x5d, wasm_op_t{"f32.lt", false, {}}},
  {0x5e, wasm_op_t{"f32.gt", false, {}}},
  {0x5f, wasm_op_t{"f32.le", false, {}}},
  {0x60, wasm_op_t{"f32.ge", false, {}}},
  {0x61, wasm_op_t{"f64.eq", false, {}}},
  {0x62, wasm_op_t{"f64.ne", false, {}}},
  {0x63, wasm_op_t{"f64.lt", false, {}}},
  {0x64, wasm_op_t{"f64.gt", false, {}}},
  {0x65, wasm_op_t{"f64.le", false, {}}},
  {0x66, wasm_op_t{"f64.ge", false, {}}},
  {0x67, wasm_op_t{"i32.clz", false, {}}},
  {0x68, wasm_op_t{"i32.ctz", false, {}}},
  {0x69, wasm_op_t{"i32.popcnt", false, {}}},
  {0x6a, wasm_op_t{"i32.add", false, {}}},
  {0x6b, wasm_op_t{"i32.sub", false, {}}},
  {0x6c, wasm_op_t{"i32.mul", false, {}}},
  {0x6d, wasm_op_t{"i32.div_s", false, {}}},
  {0x6e, wasm_op_t{"i32.div_u", false, {}}},
  {0x6f, wasm_op_t{"i32.rem_s", false, {}}},
  {0x70, wasm_op_t{"i32.rem_u", false, {}}},
  {0x71, wasm_op_t{"i32.and", false, {}}},
  {0x72, wasm_op_t{"i32.or", false, {}}},
  {0x73, wasm_op_t{"i32.xor", false, {}}},
  {0x74, wasm_op_t{"i32.shl", false, {}}},
  {0x75, wasm_op_t{"i32.shr_s", false, {}}},
  {0x76, wasm_op_t{"i32.shr_u", false, {}}},
  {0x77, wasm_op_t{"i32.rotl", false, {}}},
  {0x78, wasm_op_t{"i32.rotr", false, {}}},
  {0x79, wasm_op_t{"i64.clz", false, {}}},
  {0x7a, wasm_op_t{"i64.ctz", false, {}}},
  {0x7b, wasm_op_t{"i64.popcnt", false, {}}},
  {0x7c, wasm_op_t{"i64.add", false, {}}},
  {0x7d, wasm_op_t{"i64.sub", false, {}}},
  {0x7e, wasm_op_t{"i64.mul", false, {}}},
  {0x7f, wasm_op_t{"i64.div_s", false, {}}},
  {0x80, wasm_op_t{"i64.div_u", false, {}}},
  {0x81, wasm_op_t{"i64.rem_s", false, {}}},
  {0x82, wasm_op_t{"i64.rem_u", false, {}}},
  {0x83, wasm_op_t{"i64.and", false, {}}},
  {0x84, wasm_op_t{"i64.or", false, {}}},
  {0x85, wasm_op_t{"i64.xor", false, {}}},
  {0x86, wasm_op_t{"i64.shl", false, {}}},
  {0x87, wasm_op_t{"i64.shr_s", false, {}}},
  {0x88, wasm_op_t{"i64.shr_u", false, {}}},
  {0x89, wasm_op_t{"i64.rotl", false, {}}},
  {0x8a, wasm_op_t{"i63.rotr", false, {}}},
  {0x8b, wasm_op_t{"f32.abs", false, {}}},
  {0x8c, wasm_op_t{"f32.neg", false, {}}},
  {0x8d, wasm_op_t{"f32.ceil", false, {}}},
  {0x8e, wasm_op_t{"f32.floor", false, {}}},
  {0x8f, wasm_op_t{"f32.trunc", false, {}}},
  {0x90, wasm_op_t{"f32.nearest", false, {}}},
  {0x91, wasm_op_t{"f32.sqrt", false, {}}},
  {0x92, wasm_op_t{"f32.add", false, {}}},
  {0x93, wasm_op_t{"f32.sub", false, {}}},
  {0x94, wasm_op_t{"f32.mul", false, {}}},
  {0x95, wasm_op_t{"f32.div", false, {}}},
  {0x96, wasm_op_t{"f32.min", false, {}}},
  {0x97, wasm_op_t{"f32.max", false, {}}},
  {0x98, wasm_op_t{"f32.copysign", false, {}}},
  {0x99, wasm_op_t{"f64.abs", false, {}}},
  {0x9a, wasm_op_t{"f64.neg", false, {}}},
  {0x9b, wasm_op_t{"f64.ceil", false, {}}},
  {0x9c, wasm_op_t{"f64.floor", false, {}}},
  {0x9d, wasm_op_t{"f64.trunc", false, {}}},
  {0x9e, wasm_op_t{"f64.nearest", false, {}}},
  {0x9f, wasm_op_t{"f64.sqrt", false, {}}},
  {0xa0, wasm_op_t{"f64.add", false, {}}},
  {0xa1, wasm_op_t{"f64.sub", false, {}}},
  {0xa2, wasm_op_t{"f64.mul", false, {}}},
  {0xa3, wasm_op_t{"f64.div", false, {}}},
  {0xa4, wasm_op_t{"f64.min", false, {}}},
  {0xa5, wasm_op_t{"f64.max", false, {}}},
  {0xa6, wasm_op_t{"f64.copysign", false, {}}},
  {0xa7, wasm_op_t{"i32.wrap/i64", false, {}}},
  {0xa8, wasm_op_t{"i32.trunc_s/f32", false, {}}},
  {0xa9, wasm_op_t{"i32.trunc_u/f32", false, {}}},
  {0xaa, wasm_op_t{"i32.trunc_s/f64", false, {}}},
  {0xab, wasm_op_t{"i32.trunc_u/f64", false, {}}},
  {0xac, wasm_op_t{"i64.extend_s/i32", false, {}}},
  {0xad, wasm_op_t{"i64.extend_u/i32", false, {}}},
  {0xae, wasm_op_t{"i64.trunc_s/f32", false, {}}},
  {0xaf, wasm_op_t{"i64.trunc_u/f32", false, {}}},
  {0xb0, wasm_op_t{"i64.trunc_s/f64", false, {}}},
  {0xb1, wasm_op_t{"i64.trunc_u/f64", false, {}}},
  {0xb2, wasm_op_t{"f32.convert_s/i32", false, {}}},
  {0xb3, wasm_op_t{"f32.convert_u/i32", false, {}}},
  {0xb4, wasm_op_t{"f32.convert_s/i64", false, {}}},
  {0xb5, wasm_op_t{"f32.convert_u/i64", false, {}}},
  {0xb6, wasm_op_t{"f32.demote/f64", false, {}}},
  {0xb7, wasm_op_t{"f64.convert_s/i32", false, {}}},
  {0xb8, wasm_op_t{"f64.convert_u/i32", false, {}}},
  {0xb9, wasm_op_t{"f64.convert_s/i64", false, {}}},
  {0xba, wasm_op_t{"f64.convert_u/i64", false, {}}},
  {0xbb, wasm_op_t{"f64.promote/f32", false, {}}},
  {0xbc, wasm_op_t{"i32.reinterpret/f32", false, {}}},
  {0xbd, wasm_op_t{"i64.reinterpret/f64", false, {}}},
  {0xbe, wasm_op_t{"f32.reinterpret/i32", false, {}}},
  {0xbf, wasm_op_t{"f64.reinterpret/i64", false, {}}}
};
#endif // header guard end
/**********************************************************************************************************************/
/*last line intentionally left blank.*/

