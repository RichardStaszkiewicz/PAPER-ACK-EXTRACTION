import json
import pandas as pd
import pathlib
import os
from pybliometrics.scopus import ScopusSearch

def make_dir(name, protocol):
    if protocol == "local":
        return os.path.join(pathlib.Path(__file__).parent.resolve(), name)
    elif protocol == "workspace":
        return os.path.join(pathlib.Path().resolve(), name)

def make_query(elements, keyword, conjugator):
    answer = keyword + "("
    for e in elements:
        answer += f"{e} {conjugator} "
    answer = answer[:-(len(conjugator) + 1)]
    answer += ")"
    return answer

def write_output(search_list, config, out_file, mode="w"):
    with open(out_file, mode) as handle:
        handle.write(make_query(search_list, config['keyword'], config['conjugator']))
        handle.write('\n')
    return

def get_searchlist(df, config):
    refined = df[df[config['category']] == 'x'][df['Punkty'] > config['points_treshold']]
    search_list = pd.concat([refined[e] for e in config['extract']]).dropna().unique()
    assert len(search_list) == len(refined)
    return search_list, refined

def get_datacount(search_list, config):
    lt = []
    for x in search_list:
        q = make_query([x], config['keyword'], config['conjugator'])
        try:
            s = ScopusSearch(q,view ="STANDARD", download=False, subscriber=False, verbose=False)
            lt.append(s.get_results_size())
        except Exception as e:
            e = str(e)
            lt.append(int(e.split(" ")[1].replace(',', '')))
    return lt

def compute_queries(search_list, lt, config, out_file):
    x = []
    obj = 0
    for s, l in zip(search_list, lt):
        if obj + l < config["max_treshhold"]:
            x.append(s)
            obj += l
        elif l > config["max_treshhold"]:
            print("Excieded max treashold: ", s, " provided ", l, " responses")
        else:
            write_output(x, config, out_file, "a")
            x = [s]
            obj = l
    write_output(x, config, out_file, "a")

if __name__ == "__main__":
    with open(make_dir("scopus.config", protocol="workspace")) as handle:
        config = json.load(handle)
    xls = pd.ExcelFile(make_dir(config['file'], protocol="workspace"))
    df = pd.read_excel(xls, sheet_name=config['sheet_name'], header=config['header'])
    search_list, refined = get_searchlist(df, config)
    lt = get_datacount(search_list, config)
    compute_queries(search_list, lt, config, make_dir("scopus.queries", protocol="local"))
    #write_output(search_list, config, make_dir("scopus.answer", protocol="local"))