require_relative 'hardware.rb'

# creating SAL class
class SAL
  # declaring instance variables
  attr_accessor :opcode, :argtype
  #abstract method
  def execute
  end
  # print statement
  def SAL.print
    puts "Zero bit : #{Zerobit.get}"
    puts "Overflow bit : #{Overflowbit.get}"
    puts "Register A : #{RegisterA.get}"
    puts "Register B : #{RegisterB.get}"
    #puts "Symbol Table : #{Symbol.printsymbol}"

    #puts "Memory : #{Memory.getMemoryList}"
    # puts "Symbol Table : #{Symbol.printsymbol}"
    Symbol.print
  end
end

#declaration class
class DEC < SAL
  # initializing with argtype and opcode
  def initialize argtype
    @argtype = argtype
    @opcode = 'DEC'
  end
  # using inheritance and setting the symbol to symbol map and declaring the memory to the symbol
  def execute
    value = Memory.getvalueptr
    Symbol.set @argtype, value
    #Memory.setvalone 0
  end
end

#loading class
class LDI < SAL
  # initializing with argtype and opcode
  def initialize argtype
    #value = Memory.getvalueptr
    #Memory.setvalone argtype
    @argtype = argtype
    @opcode = 'LDI'
  end
  # storing the values to the register A
  def execute
    RegisterA.set @argtype.to_i
  end
end

# exchange class
class XCH < SAL
  # initializing with argtype and opcode
  def initialize
    @opcode = 'XCH'
  end
  # switching the values of register A and B
  def execute
    temp = RegisterA.get
    RegisterA.set RegisterB.get
    RegisterB.set temp
  end
end

# adding class
class ADD < SAL
  # initializing with argtype and opcode
  def initialize
    @opcode = 'ADD'
  end
  # adding the values of register A and B and storing it in A
  def execute
    totalsum = RegisterA.get + RegisterB.get

    #puts 'totalsum'
    #puts totalsum
    # setting the zerobit if the sum is 0
    if totalsum == 0
      Zerobit.set 1
    end
    # setting the overflow bit if the sum exceeds the range
    if totalsum > 2147483648
      RegisterA.set(totalsum - 2147483648)
      Overflowbit.set 1
    elsif totalsum < -2147483647
      RegisterA.set(2147483647 + totalsum )
      Overflowbit.set 1
    else
      RegisterA.set(totalsum)
    end
  end
end

# storing class
class STR < SAL
  # initializing with argtype and opcode
  def initialize argtype
    @opcode = 'STR'
    @argtype = argtype
  end
  # setting the value to the memory
  def execute
    Memory.setval (Symbol.get @argtype), RegisterA.get
    # puts Memory.get Symbol.get @argtype
  end
end

# jump class
class JMP < SAL
  # initializing with argtype and opcode
  def initialize argtype
    @opcode = 'JMP'
    @argtype = argtype
  end
  # jumping to the particular count
  def execute
    ProgramCounter.setinst @argtype
  end
end

# JZS class
class JZS < SAL
  # initializing with argtype and opcode
  def initialize argtype
    @opcode = 'JZS'
    @argtype = argtype
  end
  # jumping to the particular counter if the zerobit is set
  def execute
    #puts "Zerobit get is #{Zerobit.get}"
    if Zerobit.get == 1
      ProgramCounter.setinst @argtype
    end
  end
end

# JVS class
class JVS < SAL
  # initializing with argtype and opcode
  def initialize argtype
    @opcode = 'JVS'
    @argtype = argtype
  end
  # jumping to the particular counter if the overflow bit is set
  def execute
    if Overflowbit.get == 1
      ProgramCounter.setinst @argtype
    end
  end
end

# loading A class
class LDA < SAL
  # initializing with argtype and opcode
  def initialize argtype
    @argtype = argtype
    @opcode = 'LDA'
  end
  # loading the value to the A register
  def execute
    value = Symbol.get @argtype
    RegisterA.set Memory.get value
  end
end

# loading B class
class LDB < SAL
  # initializing with argtype and opcode
  def initialize argtype
    @argtype = argtype
    @opcode = 'LDB'
  end
  # loading the value to the B register
  def execute
    value = Symbol.get @argtype
    RegisterB.set Memory.get value
  end
end

# halting class
class HLT < SAL
  # initializing with argtype and opcode
  def initialize
    @opcode = 'STR'
  end
end


# a = DEC.new "SUM"
# Memory.setinst a
# b = LDI.new -10
# Memory.setinst b
# c = XCH.new
# Memory.setinst c
# d = LDI.new 20
# Memory.setinst d
# e = ADD.new
# Memory.setinst e
# h = JZS.new 7
# Memory.setinst h
# g = JMP.new 4
# Memory.setinst g
# f = STR.new "SUM"
# Memory.setinst f
# #puts "Memory : #{Memory.getMemoryList}"
#
#
# a = DEC.new "INITIAL"
# Memory.setinst a
# a = DEC.new "SUB"
# Memory.setinst a
# a = DEC.new "RESULT"
# Memory.setinst a
# a = DEC.new "INCREMENTOR"
# Memory.setinst a
# a = LDI.new 342
# Memory.setinst a
# a = STR.new "INITIAL"
# Memory.setinst a
# a = LDI.new -3
# Memory.setinst a
# a = STR.new "SUB"
# Memory.setinst a
# a = LDI.new 0
# Memory.setinst a
# a = STR.new "RESULT"
# Memory.setinst a
# a = LDI.new 1
# Memory.setinst a
# a = STR.new "INCREMENTOR"
# Memory.setinst a
# a = JZS.new 22
# Memory.setinst a
# a = LDA.new "INCREMENTOR"
# Memory.setinst a
# a = LDB.new "RESULT"
# Memory.setinst a
# a = ADD.new
# Memory.setinst a
# a = STR.new "RESULT"
# Memory.setinst a
# a = LDA.new "SUB"
# Memory.setinst a
# a = LDB.new "INITIAL"
# Memory.setinst a
# a = ADD.new
# Memory.setinst a
# a = STR.new "INITIAL"
# Memory.setinst a
# a = JMP.new 12
# Memory.setinst a
#
#
# a = DEC.new "INITIAL"
# Memory.setinst a
# a = DEC.new "SUB"
# Memory.setinst a
# a = DEC.new "RESULT"
# Memory.setinst a
# a = DEC.new "INCREMENTOR"
# Memory.setinst a
# a = LDI.new 342
# Memory.setinst a
# a = STR.new "INITIAL"
# Memory.setinst a
# a = LDI.new -3
# Memory.setinst a
# a = STR.new "SUB"
# Memory.setinst a
# a = LDI.new 0
# Memory.setinst a
# a = STR.new "RESULT"
# Memory.setinst a
# a = LDI.new 1
# Memory.setinst a
# a = STR.new "INCREMENTOR"
# Memory.setinst a
# a = JZS.new 22
# Memory.setinst a
# a = LDA.new "INCREMENTOR"
# Memory.setinst a
# a = LDB.new "RESULT"
# Memory.setinst a
# a = ADD.new
# Memory.setinst a
# a = STR.new "RESULT"
# Memory.setinst a
# a = LDA.new "SUB"
# Memory.setinst a
# a = LDB.new "INITIAL"
# Memory.setinst a
# a = ADD.new
# Memory.setinst a
# a = STR.new "INITIAL"
# Memory.setinst a
# a = JMP.new 12
# Memory.setinst a


#
# while ProgramCounter.get < 22
#
#   puts ProgramCounter.get
#   o = Memory.get ProgramCounter.get
#   puts o.opcode
#   if o.opcode == "HLT"
#     break
#   end
#
#
#   if o.opcode == "JMP" or o.opcode =="JZS" or o.opcode =="JVS"
#     if (Zerobit.get == 1 and o.opcode == "JZS") || (Overflowbit.get == 1 and o.opcode == "JVS") || (o.opcode == "JMP")
#       ProgramCounter.setinst(o.argtype)
#     else
#       ProgramCounter.set
#     end
#
#     puts ProgramCounter.get
#      # o.execute
#      # SAL.print
#      #break
#   else
#     o.execute
#     ProgramCounter.set
#     SAL.print
#   end
#   #puts ProgramCounter.get
# end



