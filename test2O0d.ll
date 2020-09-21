; ModuleID = 'test2.cpp'
source_filename = "test2.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline norecurse nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !7 {
entry:
  %retval = alloca i32, align 4
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  call void @llvm.dbg.declare(metadata i32* %x, metadata !11, metadata !DIExpression()), !dbg !12
  call void @llvm.dbg.declare(metadata i32* %y, metadata !13, metadata !DIExpression()), !dbg !14
  br label %while.body, !dbg !15

while.body:                                       ; preds = %entry, %while.end
  store i32 5, i32* %x, align 4, !dbg !16
  store i32 1, i32* %y, align 4, !dbg !18
  br label %while.cond1, !dbg !19

while.cond1:                                      ; preds = %if.end, %while.body
  %0 = load i32, i32* %x, align 4, !dbg !20
  %cmp = icmp sgt i32 %0, 0, !dbg !21
  br i1 %cmp, label %while.body2, label %while.end, !dbg !19

while.body2:                                      ; preds = %while.cond1
  %1 = load i32, i32* %x, align 4, !dbg !22
  %dec = add nsw i32 %1, -1, !dbg !22
  store i32 %dec, i32* %x, align 4, !dbg !22
  %2 = load i32, i32* %x, align 4, !dbg !24
  %cmp3 = icmp sle i32 %2, 1, !dbg !26
  br i1 %cmp3, label %if.then, label %if.end, !dbg !27

if.then:                                          ; preds = %while.body2
  store i32 0, i32* %y, align 4, !dbg !28
  br label %if.end, !dbg !29

if.end:                                           ; preds = %if.then, %while.body2
  br label %while.cond1, !dbg !19, !llvm.loop !30

while.end:                                        ; preds = %while.cond1
  br label %while.body, !dbg !15, !llvm.loop !32
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { noinline norecurse nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5}
!llvm.ident = !{!6}

!0 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus_14, file: !1, producer: "clang version 10.0.1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "test2.cpp", directory: "/home/fengwz/Desktop/llvm-project/myProject/test/test2")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{!"clang version 10.0.1 "}
!7 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 6, type: !8, scopeLine: 7, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!8 = !DISubroutineType(types: !9)
!9 = !{!10}
!10 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!11 = !DILocalVariable(name: "x", scope: !7, file: !1, line: 8, type: !10)
!12 = !DILocation(line: 8, column: 9, scope: !7)
!13 = !DILocalVariable(name: "y", scope: !7, file: !1, line: 8, type: !10)
!14 = !DILocation(line: 8, column: 12, scope: !7)
!15 = !DILocation(line: 9, column: 5, scope: !7)
!16 = !DILocation(line: 11, column: 11, scope: !17)
!17 = distinct !DILexicalBlock(scope: !7, file: !1, line: 10, column: 5)
!18 = !DILocation(line: 12, column: 11, scope: !17)
!19 = !DILocation(line: 13, column: 9, scope: !17)
!20 = !DILocation(line: 13, column: 15, scope: !17)
!21 = !DILocation(line: 13, column: 17, scope: !17)
!22 = !DILocation(line: 15, column: 14, scope: !23)
!23 = distinct !DILexicalBlock(scope: !17, file: !1, line: 14, column: 9)
!24 = !DILocation(line: 16, column: 18, scope: !25)
!25 = distinct !DILexicalBlock(scope: !23, file: !1, line: 16, column: 18)
!26 = !DILocation(line: 16, column: 20, scope: !25)
!27 = !DILocation(line: 16, column: 18, scope: !23)
!28 = !DILocation(line: 17, column: 19, scope: !25)
!29 = !DILocation(line: 17, column: 17, scope: !25)
!30 = distinct !{!30, !19, !31}
!31 = !DILocation(line: 18, column: 9, scope: !17)
!32 = distinct !{!32, !15, !33}
!33 = !DILocation(line: 19, column: 5, scope: !7)
