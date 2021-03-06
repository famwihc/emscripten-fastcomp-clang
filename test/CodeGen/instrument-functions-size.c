// RUN: %clang_cc1 -S -emit-llvm -o - %s -finstrument-functions -finstrument-functions-size 2 | FileCheck %s

// CHECK: define i32 @test1
int test1(int x) {
// CHECK-NOT: __cyg_profile_func_enter
// CHECK-NOT: __cyg_profile_func_exit
// CHECK: ret i32
  return x;
}

// CHECK: define i32 @test2
int test2(int) __attribute__((no_instrument_function));
int test2(int x) {
  if(x) {test1(x);}
// CHECK-NOT: __cyg_profile_func_enter
// CHECK-NOT: __cyg_profile_func_exit
// CHECK: ret i32
  return x;
}

// CHECK: define i32 @test3
int test3(int x) {
  if(x) {test1(x);}
// CHECK: __cyg_profile_func_enter
// CHECK: __cyg_profile_func_exit
// CHECK: ret i32
  return x;
}
