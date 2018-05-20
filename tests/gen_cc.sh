make -s re && ./test && gcov *.gcno && lcov -o test.info -c -d . && genhtml -o res test.info &>/dev/null && firefox res/index.html || chromium res/index.html;
make -s fclean
