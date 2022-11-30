import os
from binarytree import Node, get_parent
from ast import literal_eval
from math import floor, ceil

with open(os.path.join(os.path.dirname(__file__), "input"), "r") as f:
    input = f.read().splitlines()


def parse_array(arr):
    try:
        return Node(int(arr))
    except:
        pass
    root = Node(-1)
    root.left = parse_array(arr[0])
    root.right = parse_array(arr[1])
    return root


def first_left(tree: Node, node: Node):
    parent = get_parent(tree, node)
    if not parent:
        return None
    return first_left(tree, parent) if parent.left == node else right_child(parent.left)


def right_child(node: Node):
    if node.right:
        return right_child(node.right)
    return node


def first_right(tree: Node, node: Node):
    parent = get_parent(tree, node)
    if not parent:
        return None
    return first_right(tree, parent) if parent.right == node else left_child(parent.right)


def left_child(node: Node):
    if node.left:
        return left_child(node.left)
    return node


def explode(tree: Node):
    possible_nodes = [node for level in tree.levels[5:] for node in level]
    for node in tree.postorder:
        if node.value >= 0 and node in possible_nodes:
            parent = get_parent(tree, node)
            grandparent = get_parent(tree, parent)
            left_node = parent.left
            right_node = parent.right
            firstl = first_left(tree, parent)
            firstr = first_right(tree, parent)
            if firstl:
                firstl.value += left_node.value
            if firstr:
                firstr.value += right_node.value
            if grandparent.left == parent:
                grandparent.left = Node(0)
            else:
                grandparent.right = Node(0)
            break


def split(tree: Node):
    for node in tree.postorder:
        if node.value > 9:
            node.left = Node(floor(node.value / 2))
            node.right = Node(ceil(node.value / 2))
            node.value = -1
            return False
    return True


def magnitude(node: Node):
    if not node.left:
        return node.value
    return 3 * magnitude(node.left) + 2 * magnitude(node.right)


tree = parse_array(literal_eval(input[0]))
for line in input[1:]:
    line_arr = literal_eval(line)
    root = Node(-1)
    root.left = tree
    root.right = parse_array(line_arr)
    tree = root
    ok = False
    while not ok:
        ok = True
        if tree.height > 4:
            ok = False
            explode(tree)
        else:
            ok = split(tree)

print(magnitude(tree))
