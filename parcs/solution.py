from Pyro4 import expose

# Relief
kernel1 = [[-1, -1, 0],
            [-1, 0, 1],
            [0, 1, 1]]
# Edge Detection
kernel2 = [[-1, -1, -1],
                   [-1, 8, -1],
                    [-1, -1, -1]]
                 
# Negative
kernel3 = [[0,0,0],
                    [0, -1, 0],
                    [0,0,0]]
# Haussian
kernel4 = [[0.0947, 0.1183, 0.0947],
                    [0.1183, 0.1477, 0.1183],
                    [0.0947, 0.1183, 0.0947]]

# Haussian 5
kernel5 = [[1, 4, 7, 4, 1],
                    [4, 16, 26, 16, 4],
                    [7, 26, 41, 26, 7],
                    [4, 16, 26, 16, 4],
                    [1, 4, 7, 4, 1]]

k = 1

def f(w, b):
  res = [0, 0, 0]
  for t in range(3):
    for i in range(len(w)):
      for j in range(len(w[0])):
    
        res[t] += w[i][j][t]*b[i][j]
  
  for t in range(3):
    res[t] %= 256

  return tuple(res)

class Solver:
  def __init__(self, workers=None, input_file_name=None, output_file_name=None):
    self.input_file_name = input_file_name
    self.output_file_name = output_file_name
    self.workers = workers
    self.k=1
    print("Inited")

  def pad_image(self, a):
    k = self.k
    hor = [[[0]*3 for _ in range(len(a[0])+2*k)] for _ in range(k)]
    mid = [[(0,0,0)]*k + a[i] + [(0,0,0)]*k for i in range(len(a))]
    return hor[:][:][:] + mid[:][:][:] + hor[:][:][:]

  def solve(self):
    print("Job Started")
    print("Workers " , len(self.workers))
    sizes, a = self.read_input()
    a = self.pad_image(a)
    n = len(self.workers) 
    step = (sizes[0])//n

    # map
    mapped = []
    k = self.k
    for i in range(n-1):
      mapped.append(self.workers[i].mymap(a[i*step : (i+1)*step +self.k*2], k))
    mapped.append(self.workers[-1].mymap(a[(n-1)*step :], k))

 
    # output
    output = self.myreduce(mapped)
    self.write_output(output, sizes)

    print("Job Finished")


  @staticmethod
  @expose
  def mymap(a, k):
    m, n = len(a), len(a[0])
    
    res = [[[0]*3 for _ in range(n-k*2)] for _ in range(m-k*2)]
    for i in range(k, m-k):
      for j in range(k, n-k):
        res[i-k][j-k] = f(
            [a[t][j-k:j+k+1] for t in range(i-k, i+k+1)], 
            kernel5)
  
    return res

  @staticmethod
  @expose
  def myreduce(mapped):
      output = []
      for arr in mapped:
        
        output.append(arr.value)
      return output

  def read_input(self):
      f = open(self.input_file_name, 'r')
      content = f.read().split(' ')
      data = []
      sizes = [int(content[0]), int(content[1])]
      content = content[2:]
      for i in range(sizes[0]):
        row = []
        for j in range(sizes[1]):
          t = (i*sizes[1]+j)*3
          row.append((int(content[t]), int(content[t+1]), int(content[t+2])))
        data.append(row)
      f.close()
      return sizes, data

  def write_output(self, output, sizes):
      f = open(self.output_file_name, 'w')
      
      f.write(str(sizes[0])+' '+str(sizes[1])+' ')
      for part in output:
        for row in part:
          for cell in row:
            for val in cell:
              f.write(str(int(val))+' ')
      f.close()