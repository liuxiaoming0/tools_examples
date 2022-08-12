#include "gtest/gtest.h"
#include <sys/time.h>

#define ANSI_TXT_GRN "\033[0;32m" // green
#define ANSI_TXT_YEL "\033[0;33m" // yellow
#define ANSI_TXT_BLU "\033[0;33m" // blue
#define ANSI_TXT_MGT "\033[0;35m" // purple
#define ANSI_TXT_DFT "\033[0;0m"  // Console default
#define GTEST_BOX "[     cout ] "
#define COUT_GTEST ANSI_TXT_GRN << GTEST_BOX
#define COUT_GTEST_MGT COUT_GTEST << ANSI_TXT_YEL