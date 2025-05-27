import streamlit as st
import subprocess
import os

os.chdir("D:/DAA_project")

# File paths
BASE_PATH = "D:/DAA_project/"
OUTPUT_FILE = os.path.join(BASE_PATH, "OUTPUT.txt")
INPUT_FILE = os.path.join(BASE_PATH, "NEWINPUT.txt")
QUERY_FILE = os.path.join(BASE_PATH, "QUERY.txt")
CHECK_EXE = os.path.join(BASE_PATH, "check.exe")
RECOMMENDATION_EXE = os.path.join(BASE_PATH, "recommend_user.exe")

interests = [
    "AR/VR",
    "Blockchain",
    "Cybersecurity",
    "Data Science",
    "IoT",
    "ML",
    "Robotics"
]

userData = {"USERNAME" : "", "NAME" : "", "LEETCODE RANK" : "", "CGPA" : "", "INTERESTS" : ""}

def landingPage(userData, login = False):
    st.title("Welcome to your Dashboard")

    st.subheader("Your Details:")
    
    if not login:
        st.text(f"Username: {userData.get('USERNAME', 'N/A')}")
        st.text(f"Name: {userData.get('NAME', 'N/A')}")
        st.text(f"Leetcode Rank: {userData.get('LEETCODE_RANK', 'N/A')}")
        st.text(f"CGPA: {userData.get('CGPA', 'N/A')}")
        st.text(f"Interests: {', '.join(userData.get('INTERESTS', []))}")

    else:
        st.text(f"USERNAME : {userData['USERNAME']}")

# Load existing usernames by first character
userNames = {}
with open(INPUT_FILE, 'r') as file:
    for line in file:
        prop = line.strip().split()
        if len(prop) != 0 and prop[0] == "USERNAME:":
            userName = prop[1]
            idx = userName[0]
            userNames.setdefault(idx, []).append(userName)

# Login functionality
def login():
    placeholder = st.empty()
    with placeholder.form('Login'):
        st.write("Current working directory " + os.getcwd())
        st.markdown("Enter Your Details")
        userName = st.text_input("User Name")
        password = st.text_input("Password")

        submitted = st.form_submit_button(label="Login")

        if submitted:
            # Write username to QUERY.txt
            with open(QUERY_FILE, 'w') as file:
                file.write(userName + '\n')
                file.write(password)

            # Run the C++ compiled check.exe
            try:
                subprocess.run([CHECK_EXE], check=True)
            except subprocess.CalledProcessError:
                st.error("Something went wrong while verifying the user.")
                return

            # Read result from OUTPUT.txt
            with open(OUTPUT_FILE, 'r') as file:
                isExist = int(file.readline().strip())

            if not isExist:
                st.success("Match Found!!")
                landingPage(userData = {"USERNAME" : userName}, login = True)
                
                if st.form_submit_button("Get Recommendations"):
                    st.success("Recommendations will appear here (future implementation).")
                    
                    with open(QUERY_FILE, "w") as file:
                        file.write(userData["USERNAME"])
                    
                    try:
                        subprocess.run([RECOMMENDATION_EXE], check=True)
                    except subprocess.CalledProcessError:
                        st.error("Something went wrong while verifying the user.")
                        return
                    
                    with open("OUTPUT.txt", "r") as file:
                        text = file.read()
                        
                    st.write(text)
                
                else:
                    st.write("Error")
                
                
                
            else:
                st.error("No Match Found!!")

# Sign Up functionality
def signUp():
    placeholder = st.empty()
    with placeholder.form('Sign Up'):
        st.markdown("Enter Your Details")
        userName = st.text_input("User Name")
        name = st.text_input("Name")
        leetcodeRank = st.number_input("Leetcode Rank", step=1)
        cgpa = st.number_input("CGPA", format="%.2f")
        
        password1st = st.text_input("Set up password")
        password2nd = st.text_input("Confirm password")
        

        submitted = st.form_submit_button(label="Sign Up")
        
        if password1st != password2nd:
            st.error("Passwords not same")

        if cgpa > 10.0:
            st.warning("Invalid CGPA")
            return

        selectedInterests = st.multiselect("Select your interests", interests)

        if submitted:
            # Write username to QUERY.txt
            with open(QUERY_FILE, 'w') as file:
                file.write(userName)

            # Run check.exe to verify user existence
            try:
                subprocess.run([CHECK_EXE], check=True)
            except subprocess.CalledProcessError:
                st.error("Something went wrong while verifying the user.")
                return

            # Read result
            with open(OUTPUT_FILE, 'r') as file:
                ifexists = int(file.read().strip())

            if not ifexists:
                st.error("User Name already exists")
            else:
                st.success("Sign up successful")

                # Append to INPUTS.txt
                with open(INPUT_FILE, "a") as file:
                    file.write("\n")
                    file.write("USERNAME: " + userName + '\n')
                    file.write("NAME: " + name + '\n')
                    file.write("LEETCODE RANK: " + str(leetcodeRank) + '\n')
                    file.write("CGPA: " + str(cgpa) + '\n')
                    file.write("INTERESTS:")
                    for interest in selectedInterests:
                        file.write(' ' + interest + ',')
                    file.write("CONNECTIONS: " + '\n')
                    file.write("PASSWORD: " + password1st + '\n')

                    userData["USERNAME"] = (userName)
                    userData["NAME"] = (name)
                    userData["LEETCODE RANK"] = (str(leetcodeRank))
                    userData["CGPA"] = str(cgpa)
                    userData["INTERESTS"] = (selectedInterests)
            
                    landingPage(userData)

                # Update internal userNames dict
                idx = userName[0]
                userNames.setdefault(idx, []).append(userName)

# Streamlit App
st.title("Welcome to CampusConnector")

choice = st.radio("Choose", ["Login", "Sign Up"])
if choice == "Sign Up":
    signUp()
elif choice == "Login":
    login()
