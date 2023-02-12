#memory declaration and initialization
class Memory
  @@memoryList = [0]* 256
  @@instptr = 0
  @@valueptr = 128

  # getting the value of the particular index from the memory
  def Memory.get index
    return @@memoryList[index]
  end
  # setting the value in the memory with default pointer increment
  def Memory.setinst value
      @@memoryList[@@instptr] = value
      @@instptr += 1
  end
  # setting the value in the memory with given value
  def Memory.setval (key , value)
    @@memoryList[key] = value
  end
  # setting the value in the memory with default value pointer
  def Memory.setvalone (value)
    @@memoryList[@@valueptr] = value
  end
  # returning instancepointer
  def Memory.getinstptr
    @@instptr
  end
  # returning valuepointer
  def Memory.getvalueptr
    @@valueptr
  end
  # getting the entire memory
  def Memory.getMemoryList
    @@memoryList
  end
  # incrementing the valuepointer
  def Memory.increment
    @@valueptr += 1
  end
end

# Accumulated register A
class RegisterA
  @@a = 0
  #setting the value to the register
  def RegisterA.set value
    @@a = value
  end
  # getting the value from the register
  def RegisterA.get
    @@a
  end
end

# Accumulated register A
class RegisterB
  @@b = 0
  #setting the value to the register
  def RegisterB.set value
    @@b = value
  end
  # getting the value from the register
  def RegisterB.get
    @@b
  end
end

# creating the symbol hash table
class Symbol
  @@symbolmap = {}
  # setting the value to the hashmap
  def Symbol.set(key,value)
    @@symbolmap[key] = value
    Memory.increment
  end
  # getting the value from the hashmap
  def Symbol.get key
    @@symbolmap[key]
  end
  # returning the entire hashmap
  def Symbol.printsymbol
    @@symbolmap
  end

  # printing the symbol map
  def Symbol.print
    @@symbolmap.each do |key, value|
      puts " #{key} is #{Memory.get value}"
    end
  end
end

# creating the zerobit class
class Zerobit
  @@zbit = 0
  # setting the value to the zerobit
  def Zerobit.set value
    @@zbit = value
  end
  # getting the value from the zerobit
  def Zerobit.get
    @@zbit
  end
end

# creating the overflowbit class
class Overflowbit
  @@obit = 0
  # setting the value to the overflowbit
  def Overflowbit.set value
    @@obit = value
  end
  # getting the value from the overflowbit
  def Overflowbit.get
    @@obit
  end
end

# creating program counter
class ProgramCounter
  @@pc = 0
  # setting the default value to the program counter
  def ProgramCounter.set
    @@pc += 1
  end
  # setting particular value to the program counter
  def ProgramCounter.setinst value
    @@pc = value
  end
  # returning the value of the program counter
  def ProgramCounter.get
    @@pc
  end
end