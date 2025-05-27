import streamlit as st

placeholder = st.empty()
with placeholder.form():
    query = st.text_input(label="UserName")

with open("CHECK.txt", "w") as file:
    file.write(query)