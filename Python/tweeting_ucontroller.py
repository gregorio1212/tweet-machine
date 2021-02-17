 # @file tweeting_ucrocontroller.c
 # @author Gregório da Luz
 # @date January 2021
 # @brief file to tweet through microcontroller
import serial
import tweepy

#Here you put the key, secret, token and, token secret from your Twitter Developer account
key = "x90redHO7n2gRHn1IpSc8Vcor"
secret = "CmxFBjpo6uuqFhCGi6NRFAo2U7fdZx3dUmLkRx5Z8lnEa27Dwb"
access_token = "1352355518086582272-cf3da0erLLD3RvVzUjCM6lCcjmPMcD"
access_token_secret = "1k1kPXPmilplIHXPvKUis9cZso17j8IA63WhWk4kuDUlQ"

#In this line we use serial to open the serial connection between the board and the laptop
ser = serial.Serial('COM5', 9600,timeout=1)
tweets_posted = 0

#This is the function used to login in to your Twitter account
def OAuth():
    try:
        auth = tweepy.OAuthHandler(key, secret)
        auth.set_access_token(access_token, access_token_secret)
        return auth
    except Exception as e:
        return None

oauth = OAuth()
api = tweepy.API(oauth)

#Here we keep track of tweets posted so far, once it reaches the limit 5, we stop stop the program
while(tweet_posted < 5):
    tweet = ser.readline()
    if(tweet !=b''):
        api.update_status(tweet)
        tweets_posted +=1
