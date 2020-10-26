; ModuleID = '2Nested-1.bc'
source_filename = "../testCfile/2Nested-1.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@x = common dso_local global i32 0, align 4
@y = common dso_local global i32 0, align 4

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 0, i32* @x, align 4
  store i32 0, i32* @y, align 4
  %tmp = load i32, i32* @x, align 4
  %cmp = icmp sle i32 %tmp, 65534
  br i1 %cmp, label %if.end, label %if.then

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4
  br label %return

if.end:                                           ; preds = %entry
  %tmp1 = load i32, i32* @y, align 4
  %cmp1 = icmp sle i32 %tmp1, 65534
  br i1 %cmp1, label %if.end3, label %if.then2

if.then2:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4
  br label %return

if.end3:                                          ; preds = %if.end
  %tmp2 = load i32, i32* @y, align 4
  %cmp4 = icmp sge i32 %tmp2, -65534
  br i1 %cmp4, label %if.end6, label %if.then5

if.then5:                                         ; preds = %if.end3
  store i32 0, i32* %retval, align 4
  br label %return

if.end6:                                          ; preds = %if.end3
  br label %while.cond

while.cond:                                       ; preds = %while.body, %if.end6
  %tmp3 = load i32, i32* @x, align 4
  %cmp7 = icmp sge i32 %tmp3, 0
  br i1 %cmp7, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %tmp4 = load i32, i32* @x, align 4
  %tmp5 = load i32, i32* @y, align 4
  %add = add nsw i32 %tmp4, %tmp5
  store i32 %add, i32* @x, align 4
  %tmp6 = load i32, i32* @y, align 4
  %sub = sub nsw i32 %tmp6, 1
  store i32 %sub, i32* @y, align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  store i32 0, i32* %retval, align 4
  br label %return

return:                                           ; preds = %while.end, %if.then5, %if.then2, %if.then
  %tmp7 = load i32, i32* %retval, align 4
  ret i32 %tmp7
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.1 "}
