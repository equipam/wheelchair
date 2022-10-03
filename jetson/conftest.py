import os
import sys
sys.path.insert(0, "./src")

os.environ["TESTING"] = "TRUE"

#pytest_plugins = ("your_project.testrig.fixtures",)