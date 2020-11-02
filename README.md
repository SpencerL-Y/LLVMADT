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
- Algorithm: sampler model checker (DONE)
- Algorithm: symbolic model checker
- Gap between LTLf and verified logic formula

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

## 今天的问题
- 在做Checker的时候目前Fp类型的不能做，因为需要知道每一步的varIndex，每一步varIndex有两种获取方法，一种是用vector将每一步的varIndex存下来，但是这样当路径长度过长时需要的内存过大，另一种是需要时再去计算，这样的方法时间可能多一些，但是

# 10月21日 - 10月22日

## 李勰 
- CheckerSampleBased 中的tlutil的apstr到z3表达式的map有bug： PathChecker中的TLUtil和PathSampler中的TLUtil不一致（已解决）
- CheckerSampleBased 中的tlutil中的context为nullptr： tlutil新建时没有给context
## 维直
- 调研SV-COMP的一些资料，了解svcomp中例子的相关细节，以及研究如何在转换的时候支持这些特殊的格式。


## 今天发现的问题

如果将每一条语句作为一个状态，怎么去验证G x>0 这样的性质？可能出现的问题，从宏观的角度来看程序是满足 G x>0，但是如果分到每一个状态，就有可能不满足。即使我们只考虑全局变量的相关性质，也会出现不确定性的问题，这些问题应该怎么解决。

# 10月23日
## 维直

- 对SV-COMP下的termination-craft中的手动修改的例子进行运行，发现工具的问题：
    - 我们需要验证的程序如果全局变量是非确定性值的时候，我们如何检验其性质
    - 在IR转z3表达式时，如果源代码里有while(a && b)类型的语句，在IR中可能会出现phi语句，目前尚不能支持这类IR转z3表达式

## 李勰 
- 忙于内生安全项目，今日此处无进度。


# 10月24日 - 10月26日

## 李勰
- 和维直一起跑SV-COMP中的例子，目前状态是instruction间的点，可能需要修改对应到源程序语句的点. 跑过的例子：2Nested-1, Bangalore_v2, 3 self crafted cases 

- 发现问题：同一个变量多次出现下标应该用下划线分割，否则会出现tmp7_0和tmp_70难以区分的情况（已解决）

- 看TACAS审稿的文章
## 维直
- 继续看贺飞老师的文章和TACAS审稿的文章
- 完善流程图


# 第三周进度

## 维直

- FIXBUG: 运行PathSampler时，发现translator中存在Z3表达式构造的问题。C++的Z3binding中，对于二元表达式的优先级如果都相同的话，需要括号表示公式构造顺序

- 添加Instruction支持：支持PhiNode的指令，可以支持while的loop循环条件中存在conjunction或disjunction的情况

- 添加新的PathSampler：对SV-COMP benchmark的reach error进行支持，在sample的时候只要碰到reach_error()函数即返回当前路径，做path feasibility分析，如果feasible则违反性质。

## 李勰
- 继续调研SV-COMP的相关文件

- 添加对SV-COMP中的文件的解析，包括对yaml的解析，property的解析

- 实现了对reach_error的samplebased checker

- 对interprocedural的checking作了一些思考
