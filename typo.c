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
  | Author: Julien PAULI <jpauli@php.net>                                |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_typo.h"

/* If you declare any globals in php_typo.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(typo)
*/


/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("typo.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_typo_globals, typo_globals)
    STD_PHP_INI_ENTRY("typo.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_typo_globals, typo_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_typo_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_typo_init_globals(zend_typo_globals *typo_globals)
{
	typo_globals->global_value = 0;
	typo_globals->global_string = NULL;
}
*/
/* }}} */

#define DETECT_TYPO(meth) do { \
	if (zend_string_equals_literal_ci(func->name, meth)) { \
		zend_error(E_COMPILE_WARNING, meth "() typo in file %s at line %d", ZSTR_VAL(zend_get_compiled_filename()), func->start_lineno); \
	} \
} while (0);

void typo_ast_process(zend_ast *ast)
{
	zend_ast_list *last = (zend_ast_list *)ast;
	int i;

	ZEND_ASSERT(ast->kind == ZEND_AST_STMT_LIST);

	for(i=0; i<last->children; i++) {
		zend_ast *child = last->child[i];
		if (child->kind == ZEND_AST_STMT_LIST) {
			typo_ast_process(child);
		} else if (child->kind == ZEND_AST_CLASS) {
			zend_ast_decl *decl = (zend_ast_decl *)child;
			typo_ast_process(decl->child[2]);
		} else if (child->kind == ZEND_AST_METHOD) {
			zend_ast_decl *func = (zend_ast_decl *)child;
			DETECT_TYPO("_construct")
			DETECT_TYPO("_destruct")
			DETECT_TYPO("_debuginfo")
			DETECT_TYPO("_get")
			DETECT_TYPO("_set")
			DETECT_TYPO("_call")
			DETECT_TYPO("_callstatic")
			DETECT_TYPO("_wakeup")
			DETECT_TYPO("_sleep")
			DETECT_TYPO("_invoke")
		}
	}
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(typo)
{
	zend_ast_process = typo_ast_process;
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(typo)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(typo)
{
#if defined(COMPILE_DL_TYPO) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(typo)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(typo)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "typo support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ typo_functions[]
 *
 * Every user visible function must have an entry in typo_functions[].
 */
const zend_function_entry typo_functions[] = {
	PHP_FE_END	/* Must be the last line in typo_functions[] */
};
/* }}} */

/* {{{ typo_module_entry
 */
zend_module_entry typo_module_entry = {
	STANDARD_MODULE_HEADER,
	"typo",
	typo_functions,
	PHP_MINIT(typo),
	PHP_MSHUTDOWN(typo),
	PHP_RINIT(typo),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(typo),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(typo),
	PHP_TYPO_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TYPO
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(typo)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
