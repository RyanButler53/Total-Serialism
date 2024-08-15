# gui

from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import (
    QApplication,
    QLineEdit,
    QMainWindow,
    QLabel,
    QPushButton,
    QVBoxLayout,
    QHBoxLayout,
    QComboBox,
    QWidget,
    QScrollArea,
    QFrame
)
from PyQt6 import QtGui

import subprocess
import random

# Constants

TIME_SIGNATURES = [  "4/4",
            "1/4","3/8", "2/4", "5/8", "6/8",
            "3/4", "7/8", "9/8", "5/4", "11/8",
             "12/8", "6/4", "3/2", "13/8",
            "7/4", "15/8",
            ]

SINGLE_CLEF = ["violin", "viola", "cello", "bass",
        "oboe", "bassoon", "clarinet", "piccolo", "flute", 
        "trombone", "trumpet", "frenchhorn", "tuba"]

MULTI_CLEF = ["piano", "harp"]

PARAM_NAMES = ["Pitch Row", "Rhythm Row", "Articulation Row",
               "Tempo", "Time Signature", "Title", "Composer", "Number of Rows"]

INSTRUMENT_FIELDS = ["Instrument Name", "Row Numbers", "Row Types", "Dynamics Row"]

MULTI_CLEF_FIELDS = ["Instrument Name", "Right Hand Row Numbers", "Right Hand Row Types", 
                     "Left Hand Row Numbers", "Left Hand Row Numbers", "Dynamics Row"]

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
            print(f"Need exactly 12 unique numbers 0-11 in {field_name}")

    except ValueError as error:
        print(f"Error converting numbers to string in {field_name}")
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
            print(f"Need exactly {count} numbers between 0 and 11 in {field_name}")

    except ValueError as error:
        print(f"Error converting numbers to string in {field_name}")

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
            print(f"At least one invalid character in {field_name}")
    elif split == []:
        pass
    else:
        print(f"Need exactly {count} row types in {field_name}")

    return [random.choice(validStrings) for _ in range(count)]

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setFixedWidth(900)
        self.setFixedHeight(400)
        self.piece_params()
        self.intialize_instruments()

        self.full_layout = QHBoxLayout()
        self.full_layout.addLayout(self.param_layout)
        self.full_layout.addLayout(self.instruments_layout)

        self.widget = QWidget()
        self.widget.setLayout(self.full_layout)
        self.setCentralWidget(self.widget)
    
    # Piece Parameters Side
    def piece_params(self):
        """Function to call all the parts of the piece params side
        Initializes the QVbox that holds the entire piece params part"""
        self.param_layout = QVBoxLayout()
        self.param_layout.setSpacing(20)
        self.param_title()
        self.param_labels()
        self.generate_button()
        return 

    def param_title(self):
        """Gets the title and adds it to the piece params"""
        title = self.make_title("Piece Parameters")
        self.param_layout.addWidget(title)
        
    def param_labels(self):
        """Gets both the labels and input fields for the piece params
        Combines them into a QHbox and adds to piece params QVBox """
        
        labels = QVBoxLayout()
        data = QVBoxLayout()
        self.param_dict = {}
        for label_name in PARAM_NAMES:
            labels.addWidget(QLabel(label_name))
            entry_box = QLineEdit()
            data.addWidget(entry_box)
            self.param_dict[label_name] = entry_box

        # Set placehold text when appropriate
        for param_name in PARAM_NAMES[:4]:
            self.param_dict[param_name].setPlaceholderText("0 1 2 3 4 5 6 7 8 9 10 11")

        self.param_dict["Time Signature"].setPlaceholderText("4/4")
        self.param_dict["Number of Rows"].setPlaceholderText("12")

        # Add to full parameter layout
        self.param_label_pairs = QHBoxLayout()
        self.param_label_pairs.addLayout(labels)
        self.param_label_pairs.addLayout(data)
        self.param_layout.addLayout(self.param_label_pairs)

    def generate_button(self):
        """Creates the Generate Piece button and links it to the generate function"""
        self.gen_button = QPushButton("Generate Piece")
        self.gen_button.clicked.connect(self.generate)
        self.param_layout.addWidget(self.gen_button)

    # Instruments side
    def intialize_instruments(self):
        """Initializes a layout for the whole layout side and
        calls all functions to initialize it. """
        self.instruments_layout = QVBoxLayout()
        self.ins_title()
        self.ins_add_remove_button()
        self.ins_data()
        
    def ins_title(self):
        """Makes a title for the instruments side of the gui"""
        title = self.make_title("Instruments")
        self.instruments_layout.addWidget(title)

    def ins_add_remove_button(self):
        """Adds buttons to add or remove instruments"""
        button_layout = QHBoxLayout()

        # Add and link buttons
        self.single_clef_button = QPushButton("Add Single Clef Instrument")
        self.single_clef_button.clicked.connect(self.add_single_clef)
        self.multi_clef_button = QPushButton("Add Multi Clef Instrument")
        self.multi_clef_button.clicked.connect(self.add_multi_clef)

        button_layout.addWidget(self.single_clef_button)
        button_layout.addWidget(self.multi_clef_button)

        self.instruments_layout.addLayout(button_layout)
        
    def ins_data(self):
        """Creates a scroll area that has one instrument data box. """
        self.instrument_scroll = QScrollArea() # Actually do the scrolling
        self.instrument_widget = QWidget() # auxiliary widget to scroll on 
        # QVbox laout with all instruments
        self.instruments = QVBoxLayout() 
        self.instruments.setSpacing(30)
       
        # Instrument Data holds a list of dictionaries where each 
        # dict has the field mapping to a QLineEdit box with the data
        self.instrument_data = [] 

        # Adjust Scroll Settings
        self.instrument_scroll.setVerticalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOn)
        self.instrument_scroll.setHorizontalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        self.instrument_scroll.setWidgetResizable(True)

        # Link up widget to scroll
        self.instrument_widget.setLayout(self.instruments)
        self.instrument_scroll.setWidget(self.instrument_widget)
        self.instruments_layout.addWidget(self.instrument_scroll)

    # Controlling Functions
    
    def add_single_clef(self):
        """Adds an instrument"""
        instrument_layout = QHBoxLayout()
        instrument_layout.setSpacing(5)
        labels = QVBoxLayout()
        data = QVBoxLayout()
        instrument_dict = {}
        for label_name in INSTRUMENT_FIELDS:
            labels.addWidget(QLabel(label_name))
            
        instrument_name = QComboBox()
        data.addWidget(instrument_name)
        instrument_name.addItems(SINGLE_CLEF)
        instrument_dict["Instrument Name"] = instrument_name

        # Set up row numbers and types. Add appropriate placeholder data
        row_nums = QLineEdit()
        data.addWidget(row_nums)
        instrument_dict["Row Numbers"] = row_nums
        row_nums.setPlaceholderText("0 1 2 3 4 5 6 7 8 9 10 11")

        row_types = QLineEdit()
        data.addWidget(row_types)
        instrument_dict["Row Types"] = row_types
        row_types.setPlaceholderText("P I R RI P I R RI P I R RI")

        dynamics = QLineEdit()
        data.addWidget(dynamics)
        instrument_dict["Dynamics Row"] = dynamics
        dynamics.setPlaceholderText("0 1 2 3 4 5 6 7 8 9 10 11")

        # Add labels and data to the instrument layout
        instrument_layout.addLayout(labels)
        instrument_layout.addLayout(data)

        self.instrument_data.append(instrument_dict)
        self.instruments.addLayout(instrument_layout)

    def add_multi_clef(self):
        instrument_layout = QHBoxLayout()
        instrument_layout.setSpacing(5)
        labels = QVBoxLayout()
        data = QVBoxLayout()
        instrument_dict = {}
        for label_name in MULTI_CLEF_FIELDS:
            labels.addWidget(QLabel(label_name))
            
        instrument_name = QComboBox()
        data.addWidget(instrument_name)
        instrument_name.addItems(MULTI_CLEF)
        instrument_dict["Instrument Name"] = instrument_name

        # Set up row numbers and types. Add appropriate placeholder data
        for hand in ["Right", "Left"]:
            row_nums = QLineEdit()
            data.addWidget(row_nums)
            instrument_dict[f"{hand} Hand Row Numbers"] = row_nums
            row_nums.setPlaceholderText("0 1 2 3 4 5 6 7 8 9 10 11")

            row_types = QLineEdit()
            data.addWidget(row_types)
            instrument_dict[f"{hand} Hand Row Types"] = row_types
            row_types.setPlaceholderText("P I R RI P I R RI P I R RI")

        dynamics = QLineEdit()
        data.addWidget(dynamics)
        instrument_dict["Dynamics Row"] = dynamics
        dynamics.setPlaceholderText("0 1 2 3 4 5 6 7 8 9 10 11")

        # Add labels and data to the instrument layout
        instrument_layout.addLayout(labels)
        instrument_layout.addLayout(data)
        # widget.setStyleSheet("border: 1px solid black;") # Try to get a border around each instrument

        self.instrument_data.append(instrument_dict)
        self.instruments.addLayout(instrument_layout)

    def generate(self):
        """
        Extract all the data and write it to a file called params.txt 
        Launches the subprocess to generate the music"""
        text_strings = []
        for field_name in PARAM_NAMES[:3]:
            text = self.param_dict[field_name].text()
            text_strings.append(toString(clean12Nums(text, field_name)))

        # handle tempo
        try:
            tempo = int(self.param_dict["Tempo"].text())
            if tempo < 40:
                tempo = '40'
            elif tempo > 240:
                tempo = '240'
            else:
                tempo = str(tempo)
        except ValueError as error:
            tempo = '140'
        text_strings.append(tempo)

        # time signature
        if self.param_dict["Time Signature"] in TIME_SIGNATURES:
            text_strings.append(self.param_dict["Time Signature"] )
        else:
            text_strings.append("4/4")
                    
        title = self.param_dict["Title"].text()
        if title == "":
            title = "Total Serialist Piece"
        text_strings.append(title)

        composer = self.param_dict["Composer"].text()
        if composer == "":
            composer = "The Algorithm"
        text_strings.append(composer)

        count = self.param_dict["Number of Rows"].text()
        try:
            count = int(count)
        except ValueError as error:
            count = 12
        text_strings.append(str(count))

        # INSTRUMENTS
        if self.instrument_data == []:
            print("No Instruments")
            return
        
        text_strings.append(len(self.instrument_data))
        for instrument_dict in self.instrument_data:
            name = instrument_dict["Instrument Name"].currentText()
            text_strings.append(name)

            if name in MULTI_CLEF:
                for hand in ["Right", "Left"]:
                    row_nums = instrument_dict[f"{hand} Hand Row Numbers"].text()
                    row_types = instrument_dict[f"{hand} Hand Row Types"].text()
                    text_strings.append(toString(cleanAnyNums(row_nums, name, count)))
                    text_strings.append(toString(cleanRows(row_types,name, count)))
            else:
                row_nums = instrument_dict["Row Numbers"].text()
                row_types = instrument_dict["Row Types"].text()
                text_strings.append(toString(cleanAnyNums(row_nums, name,count)))
                text_strings.append(toString(cleanRows(row_types, name,count)))

            dynamics_row = instrument_dict["Dynamics Row"].text()
            text_strings.append(toString(cleanAnyNums(dynamics_row, "Dynamics Row", count)))
        
        with open("params.txt", 'w') as f:
            for line in text_strings:
                print(line, file=f)

        title_filename = ""
        title_split = title.split()
        for word in title_split[:-1]: 
            title_filename += (word + "_")
        title_filename += title_split[-1]

        subprocess.call(["sh", "score.sh", f"{title_filename}", "params.txt"])

    # Utility Functions
    def make_title(self,text) -> QLabel:
            """Makes a reasonable size title
            Returns a QLabel object"""
            title = QLabel(text)
            font = title.font()
            font.setPointSize(20)
            title.setFont(font)
            title.setAlignment(Qt.AlignmentFlag.AlignHCenter | Qt.AlignmentFlag.AlignTop)
            return title



app = QApplication([])
window = MainWindow()
window.show()  

app.exec()
