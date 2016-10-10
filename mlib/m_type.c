#include "m_type.h"
#include "m_allocator.h"
#include <string.h>
#include <stdio.h>
#include "m_except.h"

static m_type_t M_TYPE_T_CHAR = { "char", false },
				M_TYPE_T_INT = { "int", false },
				M_TYPE_T_SHORT = { "short", false },
				M_TYPE_T_LONG = {"long", false },
				M_TYPE_T_FLOAT = { "float", false },
				M_TYPE_T_DOUBLE = { "double", false },
				M_TYPE_T_STRING = { "string", false },
				M_TYPE_T_CSTRING = { "cstring", false},

				M_TYPE_T_CHAR_PTR = { "char", true },
				M_TYPE_T_INT_PTR = { "int", true },
				M_TYPE_T_SHORT_PTR = { "short", true },
				M_TYPE_T_LONG_PTR = { "long", true },
				M_TYPE_T_FLOAT_PTR = { "float", true },
				M_TYPE_T_DOUBLE_PTR = { "double", true },
				M_TYPE_T_STRING_PTR = { "string", true },
				M_TYPE_T_CSTRING_PTR = { "cstring", true},
				M_TYPE_T_PTR = {"void", true };

// TODO make them constant
m_type  M_TYPE_CHAR = &M_TYPE_T_CHAR,
		M_TYPE_INT = &M_TYPE_T_INT,
		M_TYPE_SHORT = &M_TYPE_T_SHORT,
		M_TYPE_LONG = &M_TYPE_T_LONG,
		M_TYPE_FLOAT = &M_TYPE_T_FLOAT,
		M_TYPE_DOUBLE = &M_TYPE_T_DOUBLE,
		M_TYPE_STRING = &M_TYPE_T_STRING,
		M_TYPE_CSTRING = &M_TYPE_T_CSTRING,

		M_TYPE_CHAR_PTR = &M_TYPE_T_CHAR_PTR,
		M_TYPE_INT_PTR = &M_TYPE_T_INT_PTR,
		M_TYPE_SHORT_PTR = &M_TYPE_T_SHORT_PTR,
		M_TYPE_LONG_PTR = &M_TYPE_T_LONG_PTR,
		M_TYPE_FLOAT_PTR = &M_TYPE_T_FLOAT_PTR,
		M_TYPE_DOUBLE_PTR = &M_TYPE_T_DOUBLE_PTR,
		M_TYPE_STRING_PTR = &M_TYPE_T_STRING_PTR,
		M_TYPE_CSTRING_PTR = &M_TYPE_T_CSTRING_PTR,
		M_TYPE_PTR = &M_TYPE_T_PTR;

static const char *m_type_get_type_name(m_type type){
	if(type->name == NULL){
		return "null";
	}
	return type->name;
}

void m_type_assert_type(m_type type, m_type except_type) {
	if (!m_type_equals(type, except_type)) {
		m_fatal_error_f(TYPE_INEQUIVALENCE, "%s%s cannot be cast to %s%s ", type->name,
				type->is_pointer ? "*" : "", m_type_get_type_name(except_type),
				except_type->is_pointer ? "*" : "");
	}
}

void m_type_assert_type_ptr(m_type type, bool is_ptr) {
	if (is_ptr && !type->is_pointer) {
		m_fatal_error_f(TYPE_INEQUIVALENCE, "type should be a pointer: %s", type->name);
	}
	if (!is_ptr && type->is_pointer) {
		m_fatal_error_f(TYPE_INEQUIVALENCE, "type should not be a pointer: %s",
				m_type_get_type_name(type));
	}
}

m_type m_type_new(const char *type_name, bool is_ptr) {
	//TODO 增加type管理器以便当类型已经存在时直接返回
	m_type type = (m_type) m_malloc_def(sizeof(m_type_t));
	type->name = type_name;
	type->is_pointer = is_ptr;
	return type;
}

m_type m_type_new_type(const char *type_name) {
	return m_type_new(type_name, false);
}

m_type m_type_new_ptr_type(const char *type_name) {
	return m_type_new(type_name, true);
}

bool m_type_equals(m_type lhs, m_type rhs) {
	//TODO 改进以更准确地比较类型
	return lhs->is_pointer == rhs->is_pointer && strcmp(lhs->name, rhs->name) == 0;
}

static m_type *PRIMITIVE_TYPES = NULL;

static void m_type_init_primitive_type_array(){
	m_type type_array[6] = {M_TYPE_CHAR, M_TYPE_SHORT, M_TYPE_INT, M_TYPE_LONG, M_TYPE_FLOAT,
			M_TYPE_DOUBLE};
	PRIMITIVE_TYPES = (m_type*) m_malloc(6 * sizeof(m_type), ALLOCATOR_GLOBAL);
	memcpy(PRIMITIVE_TYPES, type_array, 6 * sizeof(m_type));
}

bool m_type_is_primitive_type(m_type type){
	if(PRIMITIVE_TYPES == NULL){
		m_type_init_primitive_type_array();
	}
	for(index_t i = 0; i < 6; i++){
		if(m_type_equals(type, PRIMITIVE_TYPES[i])){
			return true;
		}
	}
	return false;
}
