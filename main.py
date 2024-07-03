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
    QWidget,
)
import subprocess
#Early UI has 2 tabs: Input from file, random. 
#Later UI will have inputting the whole graphical language. 

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Total Serialism Sheet Music Generator")
        self.setFixedWidth(300)
        self.setFixedHeight(200)

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

        inLayout = QHBoxLayout()
        self.input = QLineEdit()
        inLayout.addWidget(QLabel("Input Filename"))
        inLayout.addWidget(self.input)

        outLayout = QHBoxLayout()
        outLayout.addWidget(QLabel("Output Filename"))
        self.output = QLineEdit()
        outLayout.addWidget(self.output)

        generateButton = QPushButton("Generate")
        generateButton.clicked.connect(self.customMusic)

        self.leftLayout.addWidget(title)
        self.leftLayout.addLayout(inLayout)
        self.leftLayout.addLayout(outLayout)
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
        inputFilename = self.input.text()
        outputFilename = self.output.text()
        if (inputFilename == ""):
            return
        if outputFilename == "":
            print("No Output Filename given. Output file is Score.pdf")
            outputFilename = "score"
        outputFilename = outputFilename.rstrip(".pdf")
        subprocess.call(["sh", "score.sh", outputFilename, inputFilename])
        

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


