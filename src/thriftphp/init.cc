//
// Created by Terence on 12/02/2018.
//

#include <php.h>

#include "init.h"
#include "../parser/Program.h"

#define EMALLOC_P(t) (t*) emalloc (sizeof(t))
#define MALLOC_P(t) (t*) malloc (sizeof(t))

zend_class_entry *thriftphp_ce;

typedef struct {
    zend_object zo;
    Program* program;
} thriftphp;

static zend_object* create_handler(zend_class_entry* type) {
    zend_object* retval = MALLOC_P(zend_object);

    zend_object_handlers* handlers = EMALLOC_P(zend_object_handlers);
    memcpy(handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    handlers->clone_obj = NULL;

    retval->handlers = handlers;
    return retval;
}

PHP_METHOD (ThriftPHP, __construct) {
    char* file;
    size_t file_l;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &file, &file_l) == FAILURE) {
        return;
    }
    Program* program = new Program("hah");
}

PHP_METHOD (ThriftPHP, generate) {
}

zend_function_entry thriftphp_methods[] = {
    PHP_ME(ThriftPHP, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_FE_END
};

void initThriftPHP() {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "ThriftPHP", thriftphp_methods);
    thriftphp_ce = zend_register_internal_class(&ce TSRMLS_CC);
    thriftphp_ce->create_object = create_handler;
}

