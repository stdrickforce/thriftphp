//
// Created by Terence on 12/02/2018.
//

/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#include <php.h>
#include <ext/standard/info.h>

#include "config.h"
#include "thriftphp.h"
#include "thriftphp/init.h"

PHP_MINIT_FUNCTION (thriftphp) {
    initThriftPHP();
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION (thriftphp) {
    return SUCCESS;
}

PHP_RINIT_FUNCTION (thriftphp) {
#if defined(COMPILE_DL_THRIFTPHP) && defined(ZTS)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif
    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION (thriftphp) {
    return SUCCESS;
}

PHP_MINFO_FUNCTION (thriftphp) {
    php_info_print_table_start();
    php_info_print_table_header(2, "thriftphp support", "enabled");
    php_info_print_table_end();
}

const zend_function_entry thriftphp_functions[] = {
    PHP_FE_END
};

zend_module_entry thriftphp_module_entry = {
    STANDARD_MODULE_HEADER,
    "thriftphp",
    thriftphp_functions,
    PHP_MINIT(thriftphp),
    PHP_MSHUTDOWN(thriftphp),
    PHP_RINIT(thriftphp),
    PHP_RSHUTDOWN(thriftphp),
    PHP_MINFO(thriftphp),
    PHP_THRIFTPHP_VERSION,
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_THRIFTPHP
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif

ZEND_GET_MODULE(thriftphp)

#endif
