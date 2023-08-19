import os
import pathlib
import pandas as pd
import json

def make_dir(name, protocol):
    if protocol == "local":
        return os.path.join(pathlib.Path(__file__).parent.resolve(), name)
    elif protocol == "workspace":
        return os.path.join(pathlib.Path().resolve(), name)

def get_db_filelist(path, extension):
    files = [x for x in os.listdir(path) if x[-len(extension):] == extension]
    files = [os.path.join(path, x) for x in files]
    return files

if __name__ == "__main__":
    with open(make_dir("configs/mini.config", protocol="workspace")) as handle:
        config = json.load(handle)

    files = get_db_filelist(pathlib.Path(config['db_dir']), config['db_extension'])
    df = pd.concat([pd.read_csv(f, usecols=config['export_columns']).dropna() for f in files])
    df.drop_duplicates(subset=config["key_columns"], keep=config["keep_duplicate_strategy"]).to_csv(make_dir(config["save_dir"], protocol="workspace"), index=config["save_index"])