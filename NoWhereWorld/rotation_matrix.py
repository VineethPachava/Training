def gravity_compensate(q, acc):
  g = [0.0, 0.0, 0.0]
  
  # get expected direction of gravity
  g[0] = 2 * (q[1] * q[3] - q[0] * q[2])
  g[1] = 2 * (q[0] * q[1] + q[2] * q[3])
  g[2] = q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]
  
  # compensate accelerometer readings with the expected direction of gravity
  return [acc[0] - g[0], acc[1] - g[1], acc[2] - g[2]]


def rotote(beta,gamma){
        g_x = sin(beta)*G
        g_y = 0.5*sin(beta-gamma) - 0.5*sin(beta-gamma)
        g_z = 0.5*cos(beta-gamma) + 0.5*cos(beta-gamma)
print(g_x,g_y,g_z)
}

