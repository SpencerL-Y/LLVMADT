; ModuleID = 'test.bc'
source_filename = "../testCfile/test.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline norecurse nounwind optnone uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  br label %while.body

while.body:                                       ; preds = %while.end, %entry
  store i32 1, i32* %x, align 4
  store i32 6, i32* %x, align 4
  store i32 1, i32* %y, align 4
  br label %while.cond1

while.cond1:                                      ; preds = %if.end, %while.body
  %tmp = load i32, i32* %x, align 4
  %cmp = icmp sgt i32 %tmp, 0
  br i1 %cmp, label %while.body2, label %while.end

while.body2:                                      ; preds = %while.cond1
  %tmp1 = load i32, i32* %x, align 4
  %dec = add nsw i32 %tmp1, -1
  store i32 %dec, i32* %x, align 4
  %tmp2 = load i32, i32* %x, align 4
  %cmp3 = icmp sle i32 %tmp2, 1
  br i1 %cmp3, label %if.then, label %if.end

if.then:                                          ; preds = %while.body2
  store i32 0, i32* %y, align 4
  br label %if.end

if.end:                                           ; preds = %if.then, %while.body2
  br label %while.cond1

while.end:                                        ; preds = %while.cond1
  br label %while.body
}

attributes #0 = { noinline norecurse nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.1 "}
