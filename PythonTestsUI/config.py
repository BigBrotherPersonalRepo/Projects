'''
Configuration file for the Oriflame front-end autotest project.
Contains initialization and settings of the driver.
'''
import os
import selenium.webdriver as webdriver
from selenium.webdriver.firefox.service import Service
from selenium.webdriver.firefox.options import Options

#configuration
user_agent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:141.0) Gecko/20100101 Firefox/141.0"
firefox_driver = os.path.join(os.getcwd(), "drivers", "geckodriver.exe")
firefox_service = Service(firefox_driver)
firefox_options = Options()
firefox_options.set_preference("general.useragent.override", user_agent)
browser = webdriver.Firefox(service=firefox_service, options=firefox_options)
url = "https://oriflame.cz"