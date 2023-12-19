import copy
  
def cleanWorkflows(workflows):
    workflows = workflows.splitlines()
    res = {}
    for w in workflows:
        name, steps = w[:-1].split('{')
        res[name] = {}
        for s in steps.split(','):
            if ':' in s:
                cond, ret = s.split(':')
                res[name][cond]=ret
            else: res[name]['default']=s
    return res

def cleanItems(items):
    objs = []
    for item in items.splitlines():
        obj = {}
        for spec in item[1:-1].split(','):
            var, val = spec[:spec.find('=')], spec[spec.find('=')+1:]
            obj[var] = int(val)
        objs.append(obj)
    return objs

def do(wf, workflows, item):
    for w in workflows[wf]:
        if w == 'default': break
        if '<' in w:
            var, op, val = w[:w.find('<')], w[w.find('<')], w[w.find('<')+1:]
            if item[var] < int(val): break
        if '>' in w:
            var, op, val = w[:w.find('>')], w[w.find('>')], w[w.find('>')+1:]
            if item[var] > int(val): break
    return workflows[wf][w]
        
def part1(workflows, items):
    accept = []
    for item in items:
        wf = 'in'
        while True:
            wf = do(wf, workflows, item)
            if wf == 'R': break
            if wf == 'A': accept.append(item); break
    
    res = 0
    for item in accept:
        for _,v in item.items():
            res += v
            
    return res
    
def part2(workflows):
    wfs = [['in', {'x':[1, 4000], 'm':[1, 4000], 'a':[1, 4000], 's':[1, 4000]}]]
    intervals = []
    while wfs:
        wf, item = wfs.pop(0)
        if wf == 'R': continue
        if wf == 'A': intervals.append(item); continue
        for w in workflows[wf]:
            if w == 'default': wfs.append([workflows[wf][w], item]); break
            if '<' in w:
                var, val = w[:w.find('<')], int(w[w.find('<')+1:])
                if item[var][1] < val: wfs.append([workflows[wf][w], item]); break
                elif item[var][0] < val <= item[var][1]:
                    item1 = copy.deepcopy(item)
                    item1[var][1] = val-1              
                    wfs.append([workflows[wf][w], item1])
                    item[var][0] = val
            elif '>' in w:
                var, val = w[:w.find('>')], int(w[w.find('>')+1:])
                if item[var][0] > val: wfs.append([workflows[wf][w], item]); break
                elif item[var][0]<val+1<=item[var][1]:
                    item1 = copy.deepcopy(item)
                    item1[var][0] = val+1
                    wfs.append([workflows[wf][w], item1])
                    item[var][1] = val

    res = 0
    for interval in intervals:
        x, m, a, s = interval.values()
        res += max(0, x[1]-x[0]+1)*max(0, m[1]-m[0]+1)*max(0, a[1]-a[0]+1)*max(0, s[1]-s[0]+1)
    return res

if __name__=='__main__':
    workflows, items = open('input19.txt').read().split('\n\n')

    workflows = cleanWorkflows(workflows)
    items = cleanItems(items)
    
    res1 = part1(workflows, items)
    res2 = part2(workflows)
    
    print(f'{res1=} {res2=}')
    
