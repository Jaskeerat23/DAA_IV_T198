import streamlit as st
import subprocess
import os

def checkExist(inputFile, checkFile, outFile, userNames):
            
    print(userNames)
    
    with open(checkFile, 'r') as file:
        query = file.readline()
    
    with open(outFile, 'w') as file:
        try:
            for userName in userNames[query[0]]:
                if userName == query:
                    file.write("0")
                    return
            file.write("1")
        except KeyError:
            file.write("1")

def login():
    placeholder = st.empty()
    with placeholder.form('Login'):
        st.markdown("Enter Your Details")
        userName = st.text_input("User Name")
        
        submitted = st.form_submit_button(label = "Login")
        
        if submitted:
            outputFile = "D:/DAA_project/OUTPUT.txt"
            inputFile = "D:/DAA_project/INPUTS.txt"
            checkFile = "D:/DAA_project/CHECK.txt"
        
        
            with open(checkFile, 'w') as file:
                file.write(userName)
            
            checkExist(inputFile, checkFile, outputFile, userNames)
            
            with open(outputFile, 'r') as file:
                isExist = int(file.readline())
                
            if not isExist:
                st.success("Match Found!!")
            else:
                st.error("No Match Found!!")

def signUp():
    placeholder = st.empty()
    with placeholder.form('Sign Up'):
        st.markdown("Enter Your Details")
        userName = st.text_input("User Name")
        name = st.text_input("Name")
        leetcodeRank = st.number_input("Leetcode Rank")
        cgpa = st.number_input("CGPA")

        submitted = st.form_submit_button(label = "Sign Up")
        
        if (cgpa) > 10.0:
            st.warning("Invalid CGPA")

        outputFile = "D:/DAA_project/OUTPUT.txt"
        inputFile = "D:/DAA_project/INPUTS.txt"
        checkFile = "D:/DAA_project/CHECK.txt"
        
        if submitted:
            with open(checkFile, 'w') as file:
                file.write(userName)
            
            checkExist(inputFile, checkFile, outputFile, userNames)
            
            with open(outputFile, 'r') as file:
                ifexists = int(file.read())
            
            #Output is 0 if name exists
            if not ifexists:
                st.error("User Name already exists")
            else:
                st.success("Sign up successful")
                with open(inputFile, "a") as file:
                    file.write("\n")
                    file.write("USERNAME: " + userName + '\n')
                    file.write("NAME: " + name + '\n')
                    file.write("LEETCODE RANK: " + str(leetcodeRank) + '\n')
                    file.write("CGPA: " + str(cgpa) + '\n')
                    file.write("INTERESTS: " + '\n')
                    file.write("CONNECTIONS: " + '\n')
        


                    userNames.update({idx : [userName]})

st.title("Welcome to CampusConnector")

userNames = {}
with open("D:/DAA_project/INPUTS.txt", 'r') as file:
    for line in file:
        prop = line.split()
        
        if len(prop) != 0 and prop[0] == "USERNAME:":
            userName = prop[1]
            idx = userName[0]
            try:
                userNames[idx].append(userName)
            except:
                userNames.update({idx : [userName]})
                
choice = st.radio("Choose", ["login", "Sign Up"])
if choice == "Sign Up":
    signUp()
elif choice == "login":
    login()
# checkExist("D:/DAA_project/INPUTS.txt", "D:/DAA_project/CHECK.txt", "D:/DAA_project/OUTPUT.txt", userNames)