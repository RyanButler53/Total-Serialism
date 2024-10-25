from PyQt6.QtCore import Qt, QThreadPool
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
    QCheckBox,
)

import subprocess
import random
import utils
from utils import Worker, GeneratedPiece
import consts

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.threadpool = QThreadPool()
        self.setFixedWidth(800)
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
        self.param_layout.setSpacing(15)
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
        for label_name in consts.PARAM_NAMES:
            labels.addWidget(QLabel(label_name))
            entry_box = QLineEdit()
            data.addWidget(entry_box)
            self.param_dict[label_name] = entry_box

        # Set placehold text when appropriate
        for param_name in consts.PARAM_NAMES[:3]:
            self.param_dict[param_name].setPlaceholderText("0 1 2 3 4 5 6 7 8 9 10 11")

        self.param_dict["Time Signature"].setPlaceholderText("4/4")
        self.param_dict["Number of Rows"].setPlaceholderText("12")

        # Parts Checkbox
        self.parts_box = QCheckBox(text="Export Parts")
        labels.addWidget(self.parts_box)
        data.addWidget(QLabel())

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
        button_layout = QVBoxLayout()
        add_buttons = QHBoxLayout()
        remove_buttons = QHBoxLayout()

        # Add and link buttons
        self.single_clef_button = QPushButton("Add Single Clef Instrument")
        self.single_clef_button.clicked.connect(self.add_single_clef)
        self.multi_clef_button = QPushButton("Add Multi Clef Instrument")
        self.multi_clef_button.clicked.connect(self.add_multi_clef)
        self.clear_instruments_button = QPushButton("Clear All Instruments")
        self.clear_instruments_button.clicked.connect(self.clear_instruments)
        self.remove_one_button = QPushButton("Remove Last Instrument")
        self.remove_one_button.clicked.connect(self.remove_last)

        add_buttons.addWidget(self.single_clef_button)
        add_buttons.addWidget(self.multi_clef_button)
        remove_buttons.addWidget(self.clear_instruments_button)
        remove_buttons.addWidget(self.remove_one_button)
        button_layout.addLayout(add_buttons)
        button_layout.addLayout(remove_buttons)

        self.instruments_layout.addLayout(button_layout)
        
    def ins_data(self):
        """Creates a scroll area that has one instrument data box. """
        self.instrument_scroll = QScrollArea() # Actually do the scrolling
        self.instrument_widget = QWidget() # auxiliary widget to scroll on 
        # QVbox layout with all instruments
        self.instruments = QVBoxLayout() 
        self.instruments.setSpacing(30)

       
        # Instrument Data holds a list of dictionaries where each 
        # dict has the field mapping to a QLineEdit box with the data
        self.instrument_data = [] 
        self.instrument_widgets = [] # save widgets for deletion


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
        for label_name in consts.INSTRUMENT_FIELDS:
            labels.addWidget(QLabel(label_name))
            
        instrument_name = QComboBox()
        data.addWidget(instrument_name)
        instrument_name.addItems(consts.SINGLE_CLEF)
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

        # Make main instrument WIDGET
        instrument_widget = QWidget()
        instrument_widget.setLayout(instrument_layout)
        self.instrument_widgets.append(instrument_widget)

        self.instrument_data.append(instrument_dict)
        self.instruments.addWidget(instrument_widget)

    def add_multi_clef(self):
        instrument_layout = QHBoxLayout()
        instrument_layout.setSpacing(5)
        labels = QVBoxLayout()
        data = QVBoxLayout()
        instrument_dict = {}
        for label_name in consts.MULTI_CLEF_FIELDS:
            labels.addWidget(QLabel(label_name))
            
        instrument_name = QComboBox()
        data.addWidget(instrument_name)
        instrument_name.addItems(consts.MULTI_CLEF)
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

        # Make main instrument WIDGET and save it for deletion
        instrument_widget = QWidget()
        instrument_widget.setLayout(instrument_layout)
        self.instrument_widgets.append(instrument_widget)

        self.instrument_data.append(instrument_dict)
        self.instruments.addWidget(instrument_widget)

    def clear_instruments(self):
        if len(self.instrument_widgets) == 0:
            return 
        else:
            for ins in reversed(self.instrument_widgets):
                ins.deleteLater()
            self.instrument_data = []
            self.instrument_widgets = []

    def remove_last(self):
        if len(self.instrument_widgets) != 0:
            self.instrument_data.pop()
            self.instrument_widgets.pop().deleteLater()

    def generate(self):
        """
        Extract all the data and write it to a file called params.txt 
        Launches the subprocess to generate the music"""
        text_strings = []
        for field_name in consts.PARAM_NAMES[:3]:
            text = self.param_dict[field_name].text()
            clean_nums = utils.clean12Nums(text, field_name)
            if clean_nums == []:
                return
            text_strings.append(utils.toString(clean_nums))

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
            if self.param_dict["Tempo"].text() == "": # left blank, set random
                tempo = random.randrange(40, 240)
            elif not utils.launchDialog(f"{self.param_dict["Tempo"].text()} is not an invalid tempo. Press ok to set the tempo to 140"):
                return 
            else:
                tempo = '140'
        text_strings.append(tempo)

        # time signature
        if self.param_dict["Time Signature"].text() in consts.TIME_SIGNATURES:
            text_strings.append(self.param_dict["Time Signature"].text() )
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

        parts = self.parts_box.isChecked() # boolean to add parts
        
        # INSTRUMENTS
        if self.instrument_data == []:
            utils.launchDialog("No Instruments")
            return
        
        text_strings.append(len(self.instrument_data))
        for instrument_dict in self.instrument_data:
            name = instrument_dict["Instrument Name"].currentText()
            text_strings.append(name)

            if name in consts.MULTI_CLEF:
                for hand in ["Right", "Left"]:
                    row_nums = instrument_dict[f"{hand} Hand Row Numbers"].text()
                    row_types = instrument_dict[f"{hand} Hand Row Types"].text()
                    row_nums_clean = utils.cleanAnyNums(row_nums, name, count)
                    row_types_clean = utils.cleanRows(row_types,name, count)
                    if row_nums_clean == [] or row_types_clean == []: # Handle error
                        return 
                    text_strings.append(utils.toString(row_nums_clean))
                    text_strings.append(utils.toString(row_types_clean))
            else:
                row_nums = instrument_dict["Row Numbers"].text()
                row_types = instrument_dict["Row Types"].text()
                row_nums_clean = utils.cleanAnyNums(row_nums, f"{name}: Row Numbers", count)
                row_types_clean = utils.cleanRows(row_types,f"{name}: Row Types", count)
                if row_nums_clean == [] or row_types_clean == []: # Handle error
                    return 
                text_strings.append(utils.toString(row_nums_clean))
                text_strings.append(utils.toString(row_types_clean))

            dynamics_row = instrument_dict["Dynamics Row"].text()
            dynamics_row_clean = utils.cleanAnyNums(dynamics_row, "Dynamics Row", count)
            if dynamics_row_clean == []:
                return 
            text_strings.append(utils.toString(dynamics_row_clean))
        
        with open("params.txt", 'w') as f:
            for line in text_strings:
                print(line, file=f)

        title_filename = ""
        title_split = title.split()
        for word in title_split[:-1]: 
            title_filename += (word + "_")
        title_filename += title_split[-1]

        args = ["sh", "score.sh", f"{title_filename}", "params.txt"]
        if parts:
            args += ["-p"]
            msg = f"Score is in directory score-{title_filename} with filename {title_filename}"
        else:
            msg = f"Score is in current directory with filename {title_filename}"

        # Launch Thread from here
        worker = Worker(args)
        self.threadpool.start(worker)
        dlg = GeneratedPiece(msg, self)
        dlg.exec()

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
