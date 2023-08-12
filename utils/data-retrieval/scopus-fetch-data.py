import json
import pandas as pd
import pathlib
import os

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

def write_output(search_list, config, out_file):
    with open(out_file, "w") as handle:
        handle.write(make_query(search_list, config['keyword'], config['conjugator']))
        handle.write('\n')
    return

def get_searchlist(df, config):
    refined = df[df[config['category']] == 'x'][df['Punkty'] > config['points_treshold']]
    search_list = pd.concat([refined[e] for e in config['extract']]).dropna().unique()
    assert len(search_list) == len(refined)
    return search_list, refined


if __name__ == "__main__":
    with open(make_dir("scopus.config", protocol="local")) as handle:
        config = json.load(handle)
    xls = pd.ExcelFile(make_dir(config['file'], protocol="workspace"))
    df = pd.read_excel(xls, sheet_name=config['sheet_name'], header=config['header'])
    search_list, refined = get_searchlist(df, config)


    write_output(search_list, config, make_dir("scopus.out", protocol="local"))