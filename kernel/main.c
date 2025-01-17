#include "console.h"
#include "debug.h"
#include "init.h"
#include "interrupt.h"
#include "ioqueue.h"
#include "memory.h"
#include "process.h"
#include "stdio.h"
#include "syscall-init.h"
#include "syscall.h"
#include "thread.h"


#include "memory.h"

void kernel_thread_function(void *);
void kernel_thread_functionB(void *arg);
void u_prog_a(void);
void u_prog_b(void);
int prog_a_pid = 0, prog_b_pid = 0;

int test_var_a = 0, test_var_b = 0;
int main() {
  put_str("Kernel Started!\n");
  init_all();

  process_execute(u_prog_a, "user_prog_a");
  // process_execute(u_prog_b, "user_prog_b");

  thread_start("kernel_thread_main", 31, kernel_thread_function, "H ");
  // thread_start("kernel_thread_mainA", 31, kernel_thread_function, "A ");
  thread_start("kernel_thraed_B", 31, kernel_thread_functionB, "arg B ");
  // asm volatile("sti");
  intr_enable();
  console_put_str(" main_pid:0x");
  console_put_int(sys_getpid());
  console_put_char('\n');
  // thread_start("k_thread_a", 31, kernel_thread_function, "argA ");
  // thread_start("k_thread_b", 31, kernel_thread_functionB, "argB ");
  while (1) {
    // console_put_str("Main ");
  }
  return 0;
}
void kernel_thread_function(void *arg) {
  char *para = arg;
  console_put_str(" thread_a_pid:0x");
  console_put_int(sys_getpid());
  console_put_char('\n');
  console_put_str(" prog_a_pid:0x");
  console_put_int(prog_a_pid);
  console_put_char('\n');
  void *addr = sys_malloc(63);
  console_put_str("KernelA malloc the ");
  console_put_int((int)addr);
  console_put_char('\n');
  while (1)
    ;
}
void kernel_thread_functionB(void *arg) {
  char *para = arg;
  console_put_str(" thread_b_pid:0x");
  void *addr = sys_malloc(33);
  console_put_str("Kernel malloc the ");
  console_put_int((int)addr);
  console_put_char('\n');
  sys_free(addr);
  while (1)
    ;
}
void u_prog_a(void) {
  prog_a_pid = getpid();
  printf("HAPPYER%x\n", 23333);
  void *addr1 = malloc(256);
  void *addr2 = malloc(255);
  void *addr3 = malloc(254);
  printf(" prog_a malloc addr:0x%x,0x%x,0x%x\n", (int)addr1, (int)addr2,
         (int)addr3);
  int cpu_delay = 100000;
  while (cpu_delay-- > 0)
    ;
  free(addr1);
  free(addr2);
  free(addr3);
  addr1 = malloc(256);
  addr2 = malloc(255);
  addr3 = malloc(254);
  printf("Malloc again after free\n");
  printf(" prog_a malloc addr:0x%x,0x%x,0x%x\n", (int)addr1, (int)addr2,
         (int)addr3);
  cpu_delay = 100000;
  while (cpu_delay-- > 0)
    ;
  free(addr1);
  free(addr2);
  free(addr3);
  while (1) {
    // printf("HAPPYER%x\n",23333);
  }
}

void u_prog_b(void) {
  prog_b_pid = getpid();
  while (1) {
    // printf("HAPPYER%x\n",prog_b_pid);
  }
}
