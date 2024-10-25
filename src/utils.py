# Utility functions for gui
from PyQt6.QtCore import Qt, QRunnable, pyqtSlot
from PyQt6.QtWidgets import (
    QLabel,
    QVBoxLayout,
    QDialogButtonBox,
    QDialog
)

import random
import subprocess

class IncorrectInputDlg(QDialog):
    def __init__(self, msg, parent = None):
        super().__init__(parent)
        self.setWindowTitle("Invalid Input")

        QBtn = QDialogButtonBox.StandardButton.Ok | QDialogButtonBox.StandardButton.Cancel
        self.buttonBox = QDialogButtonBox(QBtn)
        self.buttonBox.accepted.connect(self.accept)
        self.buttonBox.rejected.connect(self.reject)

        self.msg = QLabel(msg)

        self.layout = QVBoxLayout()
        self.layout.addWidget(self.msg)
        self.layout.addWidget(self.buttonBox, alignment=Qt.AlignmentFlag.AlignHCenter)
        self.setLayout(self.layout)

class GeneratedPiece(QDialog):
    def __init__(self, msg, parent = None):
        super().__init__(parent)
        self.setWindowTitle("Generated Piece")

        QBtn = QDialogButtonBox.StandardButton.Ok 
        self.buttonBox = QDialogButtonBox(QBtn)
        self.buttonBox.accepted.connect(self.accept)

        self.msg = QLabel(f"Generating Piece\n{msg}")

        self.layout = QVBoxLayout()
        self.layout.addWidget(self.msg)
        self.layout.addWidget(self.buttonBox, alignment=Qt.AlignmentFlag.AlignHCenter)
        self.setLayout(self.layout)


class Worker(QRunnable):
    
    def __init__(self, args):
        super(Worker, self).__init__()
        self.args = args

    @pyqtSlot()
    def run(self):
        subprocess.call(self.args)


def toString(l):
    s = ""
    for x in l:
        s += f"{x} "
    return s[:-1]

def clean12Nums(num_string:str, field_name:str):
    """Cleans the input and returns a cleaned list of numbers"""
    split = num_string.split()
    try:
        nums = [int(n) for n in split]
        if sorted(nums) == list(range(12)):
            return nums
        elif split == []:
            pass
        else:
            msg = f"Need exactly 12 unique numbers 0-11 in {field_name}"
            msg += "\nClick OK to generate 12 random numbers"
            result = launchDialog(msg)
            if not result:
                return []
            
    except ValueError as error:
        msg = f"Error converting numbers to string in {field_name}"
        msg += "\nClick OK to generate 12 random numbers"
        if not launchDialog(msg):
            return
    nums = list(range(12))
    random.shuffle(nums)
    return nums

def cleanAnyNums(num_string:str, field_name:str, count:int):
    """Cleans any string of numbers and doesn't require the
    input to be the numbers between 0-11. Requires the 
    number of numbers in the string to be equal to count
    """
    split = num_string.split()
    try:
        nums = [int(n) for n in split]
        if split == []:
            pass
        elif all(map(lambda x: 0 <= x < 12, nums)):
            return nums
        else:
            msg = f"Need exactly {count} numbers between 0 and 11 in {field_name}"
            msg += f"\nClick ok to generate {count} random numbers\nbetween 0 and 11 in {field_name}"
            if not launchDialog(msg):
                return

    except ValueError as error:
        msg = f"Error converting numbers to string in {field_name}"
        msg += f"\nClick ok to generate {count} random numbers\nbetween 0 and 11 in {field_name}"
        if not launchDialog(msg):
            return

    # If there are exactly 12 numbers then do the 0-11 perfect random
    if count == 12:
        return clean12Nums("","")
    else: # otherwise just fill it with random stuff.
        return [random.choice(range(12)) for _ in range(count)]

def cleanRows(row_str:str, field_name:str, count:int):
    """Cleans a list of strings for rows and returns a valid list of rows"""
    row_str.upper()
    split = row_str.split()
    validStrings = ["P", "R", "I", "RI"]
    if len(split) == count:
        if all([x in validStrings for x in split]):
            return split
        else:
            msg = f"At least one invalid character in {field_name}"
            msg += f"\nClick ok to generate {count} row types for {field_name}"
            if not launchDialog(msg):
                return
    elif split == []:
        pass
    else:
        msg = f"Need exactly {count} row types in {field_name}"
        msg += f"\nClick ok to generate {count} row types for {field_name}"
        if not launchDialog(msg):
            return

    return [random.choice(validStrings) for _ in range(count)]

def launchDialog(msg:str):
    dlg = IncorrectInputDlg(msg)
    return dlg.exec()