a = 10
b = a
c = 10
d = "hello"
e = d
f = "hello"
g = :hello
h = :hello
i = g
puts a.equal?(b)
puts a.equal?(c)
puts c.equal?(b)
puts e.equal?(d)
puts e.equal?(f)
puts e.eql?(f)
puts g.equal?(h)
puts g.equal?(i)
