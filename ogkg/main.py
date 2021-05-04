from scipy.spatial import Voronoi, voronoi_plot_2d
import numpy as np
import matplotlib.pyplot as plt
import random


def gen_points(num):
    p = [[random.randint(-500, 500), random.randint(-500, 500)] for i in range(num)]
    points = []
    for point in p:
        if point not in points:
            points.append(point)
    return points


def read_from_file(filename):
    f = open(filename, 'r')
    points, p = [], []
    for num in f.read().split(' '):
        p.append(float(num))

    for i in range(0, len(p), 2):
        point = [p[i], p[i + 1]]
        if point not in points:
            points.append(point)
    return points


def check_points(points):
    p = points[:]
    points = []
    for point in p:
        if point not in points:
            points.append(point)


def solve(points):
    check_points(points)
    print(points)
    points.sort()
    n = len(points)
    if (n < 3):
        print("too few points")
        return
    voronoi = Voronoi(points)
    vertices = voronoi.vertices

    ch = []


    def vector_len(v):
        return np.sqrt(v[0]**2 + v[1]**2)


    # return angle two vectors, where second point is common
    def angle_for_points(threePoints):
        pa = threePoints[0]
        pb = threePoints[1]
        pc = threePoints[2]
        vba = make_vector(pb, pa)
        vbc = make_vector(pb, pc)
        sq = vbc[0]*vba[1] - vbc[1]*vba[0]

        angle = np.arccos((vba[0] * vbc[0] + vba[1] * vbc[1]) / (vector_len(vba) * vector_len(vbc)))
        angle_v = np.arcsin(sq / (vector_len(vba) * vector_len(vbc)))

        if angle_v > 0:
            angle = 2*np.pi-angle

        return angle


    # sort points by ascending it angle related to head_point
    def sort_by_angle(first_point, head_point):
        angles = []
        for i in range(n):
            angles.append([angle_for_points([first_point, head_point, points[i]]), i])
        angles.sort()

        return [angles[i][1] for i in range(n)]


    # build CH graham algo
    def graham():
        # find three non-colinear points
        k = 0
        while angle_for_points(points[k:k+3]) == 180.0 and k < n:
            k += 1
        if k == n:
            return []

        # pk is a center of some three points
        pk = [
            (points[k + 1][0] + points[k][0] + points[k + 2][0]) / 3,
            (points[k + 1][1] + points[k][1] + points[k + 2][1]) / 3
        ]

        # change the start point todo

        # sorted points by angle related to p[k] with head in pk
        sorted_points = sort_by_angle(points[k], pk)
        print(sorted_points)

        # graham
        a, b, c = k, k + 1, k + 2
        size = n
        used = [0 for i in range(n)]
        while sum(used) < n:
            a %= size
            b %= size
            c %= size
            if a==b:
                b += 1
                b %= size
            if b==c:
                c+=1
                c %= size
            pa = points[sorted_points[a]]
            pb = points[sorted_points[b]]
            pc = points[sorted_points[c]]

            used[sorted_points[b]] = 1

            angle = 2*np.pi - angle_for_points([pa, pb, pc])

            if angle >= np.pi:
                sorted_points.remove(sorted_points[b])
                size -= 1
                b -= 1
                a -= 1
                c -= 1
            else:
                a += 1
                b += 1
                c += 1
        return sorted_points


    # radius len for two points
    def radius(p, q):
        return np.sqrt((p[0]-q[0])**2 + (p[1]-q[1])**2)


    def make_vector(p, q):
        return [q[0] - p[0], q[1] - p[1]]


    ch = graham()
    print(ch)
    chl = len(ch)


    # check if point is inside CH (ch points are NOT inside)
    def is_in_ch(p):
        m = len(ch)
        a = points[ch[-1]]
        b = points[ch[0]]
        sign = 1 if ((b[0]-a[0])*(p[1]-a[1]) - (b[1]-a[1])*(p[0]-a[0])) > 0 else -1
        for i in range(m-1):
            a = points[ch[i]]
            b = points[ch[i+1]]
            s = 1 if ((b[0]-a[0])*(p[1]-a[1]) - (b[1]-a[1])*(p[0]-a[0])) > 0 else -1
            if s != sign:
                return False
        return True


    # return point which is projection of point onto line (p, q)
    def project_point(point, p, q):
        v = make_vector(p, q)

        if v[0] == 0:
            return [point[0], p[1]]
        if v[1] == 0:
            return [p[0], point[1]]
        k1 = v[1] / v[0]
        k2 = -1 / k1

        x = (p[1] - k1*p[0] - point[1] + k2*point[0]) / (k2 - k1)
        y = k1 * x + p[1] - k1*p[0]
        return [x, y]


    # return the list of triple points: i-th element in list in a set of three
    # points, that for vertice i are neighbours
    def find_neighbours():
        neighbours = [[] for i in range(len(voronoi.vertices))]
        for i in range(n):
            region = voronoi.regions[voronoi.point_region[i]]
            for v in region:
                if v >= 0:
                    neighbours[v].append(i)
        return neighbours


    # return the list of circles with the biggest radius
    def find_centers():
        # list of smallest radiuses for each voronoi vertex
        rads = []
        # list of voronoi vertexes - centres of circle
        ans = []

        neighbours = find_neighbours()

        for v in range(len(neighbours)):
            # do not check the vertex if it is outside the CH
            if not is_in_ch(vertices[v]):
                continue

            # potential radius and center
            rad = np.inf
            point = []
            for i in neighbours[v]:

                if radius(points[i], vertices[v]) <= rad:
                    rad = radius(points[i], vertices[v])
                    point = vertices[v]
            #print(rad)

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
            if rad:
                rads.append(rad)
                ans.append(point)


            # after all neighbours are checked, check if circle is inside the CH


        print(rads)
        print(ans)
        return [rads, ans]

    [rads, ans] = find_centers()
    if len(rads) == 0:
        print("didnt find")
        exit()
    # drawing
    #voronoi_plot_2d(voronoi)
    i = 0
    for point in points:
        plt.plot(point[0], point[1], marker='o')
        plt.text(point[0], point[1], str(i))
        i += 1
    lim = max(np.max(points), 20)
    plt.xlim(-lim, lim)
    plt.ylim(-lim, lim)

    # get list of answers
    max_rad = max(rads)
    indices = [i for i, value in enumerate(rads) if value == max_rad]
    centres = []
    for i in indices:
        centres.append(ans[i])

    print(centres)

    for point in centres:
        circle = plt.Circle((point[0], point[1]), max_rad, fill=False)
        for i in range(len(ch)):
            p = points[ch[i]]
            q = points[ch[(i+1) % len(ch)]]
            plt.plot([p[0], q[0]], [p[1], q[1]], marker='o')
        plt.gca().add_patch(circle)
    plt.plot()


points = []