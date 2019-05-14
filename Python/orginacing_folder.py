import re
import shutil
from pathlib import Path
import argparse
import string
import os

#Orginacing a folder that is full of tv shows and movies

# Helper function to move files
def acronym(name, file):
    parts = file.parts
    tv_name = tv_shows_name(parts[-2])
    tv_name = tv_name.title()
    n = ''
    for i in tv_name:
        if i.isupper():
            n += i
    return n.title() == name

def move_file(tv_name, tv_season,file):
    # In case we need to rename duplicate files
    counter = 0
    dest_show = os.path.join(Path(args.target), tv_name)  # Path(args.target) / tv_name
    dest_season = os.path.join(dest_show, tv_season)  # Path(args.target) + os.sep + tv_name  + os.sep + tv_season
    dest_show_season = os.path.join(dest_season, file.name)

    try:  # Create folders for shows and seasons
        Path(dest_show).mkdir(parents=True, exist_ok=True)
        Path(dest_season).mkdir(parents=False, exist_ok=True)
    except FileExistsError:
        # Pass if folder exists
        pass
    try:  # Move file to correct show/season
        shutil.move(str(file), dest_show_season)
    except:  # Rename and move if show aldready exists
        file.rename(dest_season / (file.name + str(counter)))
        counter += 1

# Helper funciton to find name of show
def tv_shows_name(n):
    name = ''.join(str(n))
    name = re.sub(r'[\.\_\-\!]', ' ', name)
    name = re.sub(r'[\'\(\)]', '', name)
    name = re.sub(r'[12][0-9]{3}', '', name)
    name = re.sub(r'([\(\[]).*?([\)\]]\s*-*)', '', name)
    name = re.sub(r'(Season \d*|season \d*)', '', name)
    name = re.sub(r'(S\d{2}E\d{2}|s\d{2}e\d{2})', '', name)
    return string.capwords(name)

# Helper funciton to find season of show
def season_number(n):
    sname = ''.join(n)
    sname = sname.replace(' ', '')
    if 'Season' in sname or 'season' in sname:
        s = re.findall('\d+', sname)
        st = ''.join(s)
        return 'Season ' + st.zfill(2)
    elif sname[0] == 'S' or sname[0] == 's':
        if sname[2].isalpha():
            sname = sname[1].zfill(2)
        else:
            sname = sname[1:3].zfill(2)
        return 'Season ' + sname
    elif sname[0].isdigit():
        sname = sname[0].zfill(2)
        return 'Season ' + sname
    elif sname[0] == '[':
        return 'Season ' + sname[1].zfill(2)
    elif sname.isdigit():
        sname = sname.zfill(2)
        return sname


def sort_sort(args):
    # Files we want to locate
    file_type = ('.avi', '.mp4', '.mkv', '.mpg')
    # Source folder
    p = Path(args.downloads)
    # Find files with the name,season number, and episode number in title
    find_show = re.compile(r'((.*)[\d\w \().\-]*)[ .]([^()x]?[Ss]?\d{1,2}\s?[Eex.]\s?\d{1,2}|\d{3}|Season+\s\d|season+\s\d)[^\d{3}pMBmbHD]')
    # Find shows with season number, and episode number in title but no name
    find_show_different = re.compile(r'^([sS]\d{2}[Ee]\d{2}|^\d{3,4}[a-zA-Z]+|\d{2}.)|(\w*)\s(\d{4})')
    # Shows that are only represented by three or four digits
    find_show_only_numbers = re.compile(r'(^\d{3}\.)')
    # Ignore samples
    sample_check = re.compile(r'Bloopers|bloopers|sample|Sample')
    # Extra check for season number
    season_check = re.compile(r'(S\d{1,2}E\d{2}|s\d{2}e\d{2})')

    for file in p.parent.glob('**/*'):
        if file.suffix in file_type:
            if not re.search(sample_check, file.name):
                if re.search(find_show, file.name):
                    shows = re.search(find_show, file.name)
                    tv_name = tv_shows_name(shows[1])  # Find the name of the show
                    # Find the season of the show
                    if re.search(season_check,shows[1]):
                        s = re.search(r'(.*)(S\d{1,2}E\d{2}|S\d{1,2}E\d{2})',shows[1])
                        tv_season = season_number(s[2])
                        tv_name = tv_shows_name(s[1])
                    else:
                        tv_season = season_number(shows[3])
                    if acronym(tv_name, file):
                        parts = file.parts
                        tv_name = tv_shows_name(parts[-2])
                    move_file(tv_name,tv_season,file)
                # We have to look at parent folders to find show name and season
                elif re.search(find_show_different, file.name) or re.search(find_show_only_numbers, file.name):
                    # Only look at shows that dont lie in the source folder
                    if str(file.parent) != args.downloads and not re.search(r'[12][0-9]{3}',file.name):
                        parts = file.parts
                        season = re.findall('\d+', str(parts[-2]))
                        tv_season = season_number(season)
                        tv_name = tv_shows_name(parts[-3])
                        move_file(tv_name, tv_season, file)


parser = argparse.ArgumentParser()
parser.add_argument('downloads', default='downloads', nargs='?')
parser.add_argument('target', default='target', nargs='?')
args = parser.parse_args()
sort_sort(args)
