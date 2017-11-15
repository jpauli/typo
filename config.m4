dnl $Id$
dnl config.m4 for extension typo

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(typo, for typo support,
dnl Make sure that the comment is aligned:
dnl [  --with-typo             Include typo support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(typo, whether to enable typo support,
dnl Make sure that the comment is aligned:
[  --enable-typo           Enable typo support])

if test "$PHP_TYPO" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-typo -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/typo.h"  # you most likely want to change this
  dnl if test -r $PHP_TYPO/$SEARCH_FOR; then # path given as parameter
  dnl   TYPO_DIR=$PHP_TYPO
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for typo files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       TYPO_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$TYPO_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the typo distribution])
  dnl fi

  dnl # --with-typo -> add include path
  dnl PHP_ADD_INCLUDE($TYPO_DIR/include)

  dnl # --with-typo -> check for lib and symbol presence
  dnl LIBNAME=typo # you may want to change this
  dnl LIBSYMBOL=typo # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $TYPO_DIR/$PHP_LIBDIR, TYPO_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_TYPOLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong typo lib version or lib not found])
  dnl ],[
  dnl   -L$TYPO_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(TYPO_SHARED_LIBADD)

  PHP_NEW_EXTENSION(typo, typo.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
