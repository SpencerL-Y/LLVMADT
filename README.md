# LLVMADT

# Collarborators
- Xie Li
- Weizhi Feng
- Yong Li
- Jiaxiang Liu

# WorkLog

## Xie Li
- Gap of Automaton and gwt
- Gap of Automaton and CFA  
    (DONE)
- Gap of gwt and LTLf 
- Path checker for simple LTLf
    (DONE)
- Recursive parser of LTLf
- Algorithm: sampler model checker
- Algorithm: symbolic model checker

# 开发日志

# 10月14日

## 李勰
- 实现了模块 CheckerSampleBased, 发现问题验证的时候出现了spot会将LTL公式 $\mathbf{G} x>0$ 中的$x>0$当作一个原子命题，这样就不能从LTL公式中得到$x > 0$这样的Z3表达式了，解决的办法：添加一个map，将$a$和$x > 0$map起来，然后写公式的时候写$\mathbf{G}a$, 生成Z3表达式的时候就可以map回来。

## 维直
- 在 Translator 中添加了SSA变量下标的翻译，添加了一个Map来记录路径上出现的同一个变量的次数，从而生成有意义的Z3表达式。

## 发现但尚未解决的问题

- 目前的验证只能对线性程序，因为我们的cfa上的边村的是z3表达式，应该保留从ir中获得的更多信息，因此应该存llvmapi中的instruction，在sample path的时候再生成
z3表达式。问题的核心：语法和语义。。

# 10月15日

## 李勰
- 处理昨天的问题，增加了存llvm::Instruction*的LetterTypeInst

## 维直

- 处理昨天的问题，将Converter中的LLVM2CFA修改，可以得到边上记录llvm::Instruction*并且状态上有Basicblock名称的CFA

## 需要继续解决的问题
- Converter中的CFA2DFA需要李勰修改为Inst，Inst到Z3表达式的转换的使用需要维直之后修改PathSampler并和PathChecker对接。
## Mark
- 今天进度缓慢的原因是parseIRFile得到的数据结构必须放在Main函数中，如果放在局部变量里传不出来。

# 10月16日 ~ 10月19日

## 李勰
- 将Converter中的CFA2DFA从之前的z3表达式转为了instruction的存储
- Pathchecker的debug和运行
- 调试LTLf到Automaton并跑通简单的SamplebasedChecker

## 维直
- 将llvm2cfa和pathsampler中的问题修改完成
    - llvm2cfa判断跳转指令的后继状态进行了debug和修改
- 从instruction到z3expression的问题已经解决：
    - 变量加下标的问题
    - store的处理从之前的true改为一个表达式

