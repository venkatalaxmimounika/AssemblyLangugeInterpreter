require_relative 'instruction.rb'

# reading the file from the user
puts "enter filename : "
inputfile = gets.chomp
size = 0
# iterating through all the lines of the file
linesize = 0
File.readlines(inputfile).each do |line|
  eachline = line.split(' ')
  size += 1
  if eachline[0] == 'HLT'
    a = eval(eachline[0]).new
    Memory.setinst a
    break
  end
  # calling the particular instruction class depending on the instruction

  if eachline[1]
    a = eval(eachline[0]).new eachline[1]
    Memory.setinst a
  else
    a = eval(eachline[0]).new
    Memory.setinst a
  end
  linesize +=1
end
temp = 0
# getting the instruction
while true
  puts "----------------------------------------------------------------------------"
  puts "enter command a for the execution of entire file"
  puts "enter command s for a single line execution"
  puts "enter q for quitting the loop"
  puts "enter command : "
  inputflow = gets.chomp
  case inputflow
    # executing each line if the command is s
    when "s"
      #puts ProgramCounter.get
      o = Memory.get ProgramCounter.get
      # puts o.opcode
      # halting if the command is HLT
      if o.opcode == "HLT"
         break
      end
      # setting the program counter to the given value if the following commands are given
      if o.opcode == "JMP" or o.opcode =="JZS" or o.opcode =="JVS"
        if (Zerobit.get == 1 and o.opcode == "JZS") || (Overflowbit.get == 1 and o.opcode == "JVS") || (o.opcode == "JMP")
          ProgramCounter.setinst(o.argtype.to_i)
          # setting the program counter with default value
        else
          ProgramCounter.set
        end
      else
        o.execute
        ProgramCounter.set
      end
      SAL.print
      puts "next Instruction: #{ProgramCounter.get}"
      if ProgramCounter.get == linesize
        break
      end

      # executing the entire instruction file if the command is a
  when "q"
    break

  when "a"
    # iterating through the entire instruction file
      while ProgramCounter.get < size

        #puts ProgramCounter.get
        o = Memory.get ProgramCounter.get
        #puts o.opcode
        # breaking the loop if the instruction is HLT
        # puts '22222222'
        # puts o.opcode
        if o.opcode == "HLT"
          break
        end
        # setting the program counter to the given value if the following commands are given
        if o.opcode == "JMP" or o.opcode =="JZS" or o.opcode =="JVS"
          if (Zerobit.get == 1 and o.opcode == "JZS") || (Overflowbit.get == 1 and o.opcode == "JVS") || (o.opcode == "JMP")
            ProgramCounter.setinst(o.argtype.to_i)
            # setting the program counter with default value
          else
            ProgramCounter.set
          end
        else
          o.execute
          ProgramCounter.set
        end
        if temp == 1000
          puts "you have reached 1000 instructions. press c if you want to execute the code, q otherwise"
          input = gets.chomp
          if input == 'q'
            break
          end
        end
        # SAL.print
        temp = temp+1
      end

      SAL.print
    break
  end
end
puts 'all commands got executed'

# while ProgramCounter.get < size - 1
#
#   #puts ProgramCounter.get
#   o = Memory.get ProgramCounter.get
#   #puts o.opcode
#   if o.opcode == "HLT"
#     break
#   end
#
#
#   if o.opcode == "JMP" or o.opcode =="JZS" or o.opcode =="JVS"
#     if (Zerobit.get == 1 and o.opcode == "JZS") || (Overflowbit.get == 1 and o.opcode == "JVS") || (o.opcode == "JMP")
#       ProgramCounter.setinst(o.argtype.to_i)
#     else
#       ProgramCounter.set
#     end
#
#     #puts ProgramCounter.get
#      # o.execute
#      # SAL.print
#      #break
#   else
#
#     o.execute
#     ProgramCounter.set
#
#   end
#   #puts ProgramCounter.get
# end
