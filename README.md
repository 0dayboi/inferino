# inferino
NASA Space Apps 2018 (Spot That Fire Challange) Team Macprofessionals, Project Name : Inferino
nferino is a system which consists of a autonomous drone, administrator application, server and user application. The drone has a cluster of sensors that were made to detect heat and smoke, as well as a camera to take pictures from a high altitude (that can further be used for image processing), checking on the status of the area. It allows us to scan large regions for data regarding potential and ongoing wildfires. The drone owners (such as firefighters) can set a certain period of time (for instance, once every two or three hours) and the drone will firstly check for if the terrain is clear to launch (for example, it won't launch when there's rain or snow) and start collecting information at a regular interval, loading all of it onto an SD card and building it up into a database. Whenever the sensor finds an anomaly, it will collect significantly more input. We can also use the capability of a drone to communicate with other drones, and exchange data.

Once the drone completes its mission and returns to the base, the administrators can connect to the drone via bluetooth technology, and download the data the drone has collected. After downloading, the administrators can inspect the data or upload it directly to our servers for further analysis (you can see our administrator app screenshot here: https://drive.google.com/open?id=1IMx1bsd48iuvgt7n...).

After the scanned data is uploaded to our servers, the integrated deep-learning machine can now start analyzing the data from the scanned location, and with other past incidents that were on that particular area using the open data from NASA and NASA-affiliated organizations such as FIRMS (Fire Information Resource Management System) or INCIWEB. Or it can just analyze data from the drone (if no incident was ever recorded on that area).

When the analysis is finished, the server will update its database along with the user app, so users can view the nearby wildfire analysis. In case the probability of fire which is calculated by the data deep learning system is higher than 40%, then the app will automatically send notification to nearby residents and inform the firefighting services. Or if it has already detected fire using the flame sensor then it will send an emergency alert to all the users.

(Our user app screenshots can be seen here: https://drive.google.com/open?id=1qK3U_Vt8jGMFVpbD...)

The drone is fueled by two power sources: solar energy during the day, and a rechargeable battery during the night (which can also be used as backup power). It will be a solution that saves energy and doesn’t negatively affect the environment.

