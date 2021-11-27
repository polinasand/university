# optimization
# find biggest empty circle that is inside CH (almost always) with center based on Voronoi edge
def find_centers_ch(neighbours, v, points):
    for i in range (len(neighbours[v])):
        paind = neighbours[v][i]
        pbind = neighbours[v][(i+1) % len(neighbours[v])]
        pa = points[paind]
        pb = points[pbind]
        if paind in ch:
            if pbind in ch:
                projection = project_point(vertices[v], pa, pb)
                rad_ = radius(vertices[v], projection)
                if rad_ <= rad:
                    rad = rad_
                    point = vertices[v]
            else:
                ind = ch.index(paind)
                pc_left = points[ch[ind - 1]]
                pc_right = points[ch[(ind + 1) % len(ch)]]
                projection_left = project_point(vertices[v], pc_left, pa)
                projection_right = project_point(vertices[v], pc_right, pa)
                rad_left = radius(vertices[v], projection_left)
                rad_right = radius(vertices[v], projection_right)

                if rad_left <= rad:
                    rad = rad_left
                    point = vertices[v]
                if rad_right <= rad:
                    rad = rad_right
                    point = vertices[v]
        if pbind in ch:
            ind = ch.index(pbind)
            pc_left = points[ch[ind - 1]]
            pc_right = points[ch[(ind + 1) % len(ch)]]
            projection_left = project_point(vertices[v], pc_left, pb)
            projection_right = project_point(vertices[v], pc_right, pb)
            rad_left = radius(vertices[v], projection_left)
            rad_right = radius(vertices[v], projection_right)

            if rad_left <= rad:
                rad = rad_left
                point = vertices[v]
            if rad_right <= rad:
                rad = rad_right
                point = vertices[v]