#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int
main(int argc, char *argv[])
{
  // this section will test out the trace system call
  printf(1, "%s\n", "try.c has started...");
  trace(1);
  wait();
  printf(1, "total system calls: %d\n", trace(0));
  // this section will test out the csinfo system call
  int cs1, cs2, cs3, cs4;
  cs1 = csinfo();
  cs2 = csinfo();
  sleep(1);
  cs3 = csinfo();
  sleep(1);
  cs4 = csinfo();
  printf(1, "context switch counts = %d, %d, %d, %d\n", cs1, cs2, cs3, cs4);
  exit();
}
