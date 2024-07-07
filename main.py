from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import (
    QApplication,
    QLineEdit,
    QMainWindow,
    QLabel,
    QPushButton,
    QTabWidget,
    QVBoxLayout,
    QHBoxLayout,
    QSlider,
    QWidget,
)
import subprocess
import random
#Later UI will have inputting the whole graphical language. 

def toString(l):
    s = ""
    for x in l:
        s += f"{x} "
    return s[:-1]

def cleanNums(num_string:str, field_name:str):
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

def cleanRows(row_str:str, field_name:str):
    """Cleans a list of strings"""
    row_str.upper()
    split = row_str.split()
    validStrings = ["P", "R", "I", "RI"]
    if len(split) == 12:
        if all([x in validStrings for x in split]):
            return split
        else:
            print(f"At least one invalid character in {field_name}")
    elif split == []:
        pass
    else:
        print(f"Need exactly 12 rows in {field_name}")

    return [random.choice(validStrings) for _ in range(12)]
    

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Total Serialism Sheet Music Generator")
        self.setFixedWidth(500)
        # self.setHeight(200)

        self.left_layout()
        self.right_layout()

        left = QWidget()
        left.setLayout(self.leftLayout)

        right = QWidget()
        right.setLayout(self.rightLayout)

        tabs = QTabWidget()
        tabs.setTabPosition(QTabWidget.TabPosition.North)
        tabs.setMovable(False)

        tabs.addTab(left,"Manually Input Files")
        tabs.addTab(right, "Random Music")

        self.setCentralWidget(tabs)

    def left_layout(self):

        self.leftLayout = QVBoxLayout()
        title = self.make_title("Custom Total Serial Music")
        self.leftLayout.addWidget(title)

        self.leftNumberBoxes = {} #Maps label to input field and random button
        for label in ["Pitch Row", "Rhythm Row", "Articulation Row", "Dynamic Row", "Right Hand Row Numbers", "Left Hand Row Numbers"]:
            boxLayout = QHBoxLayout()
            boxLayout.addWidget(QLabel(f"{label}: "))
            input = QLineEdit()
            input.setPlaceholderText("0 1 2 3 4 5 6 7 8 9 10 11")
            # randomButton = QPushButton("Random")
            # randomButton.clicked.connect(self.shuffle12)
            #link to something
            self.leftNumberBoxes[label] = input#,randomButton
            boxLayout.addWidget(input)
            # boxLayout.addWidget(randomButton)
            self.leftLayout.addLayout(boxLayout)
        
        self.leftRowBoxes = {}
        for label in ["Right Hand Row Types", "Left Hand Row Types"]:
            boxLayout = QHBoxLayout()
            boxLayout.addWidget(QLabel(f"{label}: "))
            input = QLineEdit()
            # randomButton = QPushButton("Random")
            input.setPlaceholderText("P I R RI P I R RI P I R RI")

            # Link the random button to something else. 
            self.leftRowBoxes[label] = input#,randomButton
            boxLayout.addWidget(input)
            # boxLayout.addWidget(randomButton)
            self.leftLayout.addLayout(boxLayout)

        # Slider
        sliderBox = QHBoxLayout()
        sliderBox.addWidget(QLabel("Tempo: 40"))
        slider = QSlider(Qt.Orientation.Horizontal)
        slider.setRange(40,240)
        slider.setSingleStep(1)
        sliderBox.addWidget(slider)
        sliderBox.addWidget(QLabel("240"))
        self.slider = slider
        self.leftLayout.addLayout(sliderBox)

        titleBox = QHBoxLayout()
        titleBox.addWidget(QLabel("Title: "))
        self.title = QLineEdit()
        titleBox.addWidget(self.title)
        self.leftLayout.addLayout(titleBox)

        composerBox = QHBoxLayout()
        composerBox.addWidget(QLabel("Composer: "))
        self.composerBox = QLineEdit()
        composerBox.addWidget(self.composerBox)
        self.leftLayout.addLayout(composerBox)

        generateButton = QPushButton("Generate")
        generateButton.clicked.connect(self.customMusic)


        self.leftLayout.addWidget(generateButton)

    def right_layout(self):

        self.rightLayout = QVBoxLayout()
        title = self.make_title("Random Music")
        self.rightLayout.addWidget(title)
        
        seedLayout = QHBoxLayout()
        self.seed = QLineEdit()
        seedLayout.addWidget(QLabel("Random Seed"))
        seedLayout.addWidget(self.seed)

        generateButton = QPushButton("Generate")
        generateButton.clicked.connect(self.randomMusic)

        self.rightLayout.addLayout(seedLayout)
        self.rightLayout.addWidget(generateButton)
        
    def make_title(self,text):
        """Makes a reasonable size title"""
        title = QLabel(text)
        font = title.font()
        font.setPointSize(20)
        title.setFont(font)
        title.setAlignment(Qt.AlignmentFlag.AlignHCenter | Qt.AlignmentFlag.AlignTop)
        return title
    
    def customMusic(self,input):
        """Calls the script with  """
        text_strings = []
        for field_name, box in self.leftNumberBoxes.items():
            nums_str = box.text()
            nums = cleanNums(nums_str, field_name)
            nums_str = toString(nums)
            text_strings.append(nums_str+ "\n")

        for field_name,box in self.leftRowBoxes.items():
            row_str = box.text()
            rows = cleanRows(row_str, field_name)
            row_str = toString(rows)
            text_strings.append(row_str+"\n")

            tempo = str(self.slider.value())
            title = self.title.text()
            if (title == ""):
                title = "Total Serialist Piece"
            composer = self.composerBox.text()
            if composer == "":
                composer = "The Algorithm"

        text_strings.append(tempo+ "\n")
        text_strings.append(title + "\n")
        text_strings.append(composer+ "\n")
        
        with open("params.txt", "w") as f:
            f.writelines(text_strings)
        title_filename = ""
        title_split = title.split()
        for word in title_split[:-1]: 
            title_filename += (word + "_")
        title_filename += title_split[-1]

        subprocess.call(["sh", "score.sh", f"{title_filename}", "params.txt"])
        
    def shuffle12(self):
        nums = list(range(0,12))
        random.shuffle(nums)
        return toString(nums)

    def randomMusic(self):
        seed = self.seed.text()
        try: #Check if seed is an integer
            seed = int(seed)
            subprocess.call(["sh", "score.sh", str(seed)])
        except ValueError as error:
            subprocess.call(["sh", "score.sh"])
        
app = QApplication([])
window = MainWindow()
window.show()  

app.exec()


