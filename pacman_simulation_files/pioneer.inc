
# Desc: Device definitions for Activemedia robots.
# Author: Richard Vaughan, Andrew Howard,  Luis Riazuelo
# Date: 10 Jun 2002
# CVS: $Id: pioneer.inc,v 1.30 2008-01-15 01:25:42 rtv Exp $





# The Pioneer2DX sonar array
define p2dx_sonar ranger
(
  scount 4 # the number of transducers
 
  # define the pose of each transducer [xpos ypos heading]
  spose[0] [ 0.0 0.130 90 ]
  spose[1] [ 0.0 -0.130 -90]
  spose[2] [ 0.03 0.0 0 ]
  spose[3] [ 0.03 0.0 180 ]
		
  # define the field of view of each transducer [range_min range_max view_angle]
  sview [0 5.0 15]

  # define the size of each transducer [xsize ysize] in meters
  ssize [0.01 0.05]
)

define p2dx_sonar_front ranger
(
  scount 8 # the number of transducers

  # define the pose of each transducer [xpos ypos heading]
  spose[0] [ 0.075 0.130 90 ]
  spose[1] [ 0.115 0.115 50 ]
  spose[2] [ 0.150 0.080 30 ]
  spose[3] [ 0.170 0.025 10 ]
  spose[4] [ 0.170 -0.025 -10 ]
  spose[5] [ 0.150 -0.080 -30 ]
  spose[6] [ 0.115 -0.115 -50 ]
  spose[7] [ 0.075 -0.130 -90 ]

  # define the field of view of each transducer [range_min range_max view_angle]
  sview [0 5.0 15]

  # define the size of each transducer [xsize ysize] in meters
  ssize [0.01 0.05]
)




# The Pioneer3DX sonar array
define p3dx_sonar ranger
(
  scount 16

  # define the pose of each transducer [xpos ypos heading]
  spose[0] [ 0.069 0.136 90 ]
  spose[1] [ 0.114 0.119 50 ]
  spose[2] [ 0.148 0.078 30 ]
  spose[3] [ 0.166 0.027 10 ]
  spose[4] [ 0.166 -0.027 -10 ]
  spose[5] [ 0.148 -0.078 -30 ]
  spose[6] [ 0.114 -0.119 -50 ]
  spose[7] [ 0.069 -0.136 -90 ]
  spose[8] [ -0.157 -0.136 -90 ]
  spose[9] [ -0.203 -0.119 -130 ]
  spose[10] [ -0.237 -0.078 -150 ]
  spose[11] [ -0.255 -0.027 -170 ]
  spose[12] [ -0.255 0.027 170 ]
  spose[13] [ -0.237 0.078 150 ]
  spose[14] [ -0.103 0.119 130 ]
  spose[15] [ -0.157 0.136 90 ]	
		
  # define the field of view of each transducer [range_min range_max view_angle]
  sview [0.1 5.0 30]  # min (m), max (m), field of view (deg)

  # define the size of each transducer [xsize ysize] in meters
  ssize [0.01 0.04]
)

# The Pioneer3AT sonar array
define p3at_sonar ranger
(
  scount 16

  # define the pose of each transducer [xpos ypos heading]
  spose[0] [0.147 0.136 90]
  spose[1] [0.193 0.119 50]
  spose[2] [0.227 0.079 30]
  spose[3] [0.245 0.027 10]
  spose[4] [0.245 -0.027 -10]
  spose[5] [0.227 -0.079 -30]
  spose[6] [0.193 -0.119 -50]
  spose[7] [0.147 -0.136 -90]
  spose[8] [-0.144 -0.136 -90]
  spose[9] [-0.189 -0.119 -130]
  spose[10] [-0.223 -0.079 -150]
  spose[11] [-0.241 -0.027 -170]
  spose[12] [-0.241 0.027 170]
  spose[13] [-0.223 0.079 150]
  spose[14] [-0.189 0.119 130]
  spose[15] [-0.144 0.136 90]

  # define the field of view of each transducer [range_min range_max view_angle]
  sview [0.1 5.0 30]  # min (m), max (m), field of view (deg)

  # define the size of each transducer [xsize ysize] in meters
  ssize [0.01 0.04]
)

define pioneer_base position 
(
  color "red"			# Default color.
  drive "diff"		 	# Differential steering model.
  gui_nose 1                  	# Draw a nose on the robot so we can see which way it points
  obstacle_return 0           	# Can hit things.
  laser_return 1                 # reflects laser beams
  ranger_return 1             	# reflects sonar beams
  blob_return 1               	# Seen by blobfinders  
  fiducial_return 1           	# Seen as "1" fiducial finders

  localization "gps"         	  
  localization_origin [0 0 0 0] 	# Start odometry at (0, 0, 0).

  # alternative odometric localization with simple error model
  # localization "odom"         		# Change to "gps" to have impossibly perfect, global odometry
  #  odom_error [ 0.05 0.05 0.1 ]   	# Odometry error or slip in X, Y and Theta
                                   	# (Uniform random distribution)   
)



define pioneer2dx_base_no_sonar pioneer_base
(
  # actual size
  size [0.5 0.5 0.22] # sizes from MobileRobots' web site

  # the pioneer's center of rotation is offset from its center of area
  origin [0.0 0.0 0 0]

  # draw a nose on the robot so we can see which way it points
  gui_nose 1

  # estimated mass in KG
  mass 23.0 
  # differential steering model
  drive "diff"
 )


define pioneer2dx_base pioneer2dx_base_no_sonar
(
  # use the sonar array defined above with a small vertical offset to
  # drop the sensors into the robot body
  p2dx_sonar( pose [0 0 -0.03 0] ) 
)

define pioneer2dx_base_front_sonar pioneer2dx_base_no_sonar
(
  # use the sonar array defined above with a small vertical offset to
  # drop the sensors into the robot body
  p2dx_sonar_front( pose [0 0 -0.03 0] ) 
)


define pioneer2dx pioneer2dx_base
(  
  # simplified Body shape:
  block( 
    points 8
    point[0] [-0.2 0.12]
    point[1] [-0.2 -0.12]
    point[2] [-0.12 -0.2555]
    point[3] [0.12 -0.2555]
    point[4] [0.2 -0.12]
    point[5] [0.2 0.12]
    point[6] [0.12 0.2555]
    point[7] [-0.12 0.2555]
    z [0 0.22]
  )
)

# as above, but with front sonar only
define pioneer2dx_front_sonar pioneer2dx_base_front_sonar
(  
  # simplified Body shape:
  block( 
    points 8
    point[0] [-0.2 0.12]
    point[1] [-0.2 -0.12]
    point[2] [-0.12 -0.2555]
    point[3] [0.12 -0.2555]
    point[4] [0.2 -0.12]
    point[5] [0.2 0.12]
    point[6] [0.12 0.2555]
    point[7] [-0.12 0.2555]
    z [0 0.22]
  )
)


# a Pioneer 2 or 3 in standard configuration
define fancypioneer2dx pioneer2dx_base
(
  # this set of blocks approximates the shape of a real Pioneer

  #  The geometry is from the Webots v5.3.0 manual. Thanks to Webots
  #  and Olivier Michel. If Stage or Gazebo do not do what you want,
  #  take a look at Webots. It's a very nice commercial simulator.
 
  # main body
  block 
  (
    points 8
    point[0] [ -0.185 -0.135 ] 
    point[1] [  0.095 -0.135 ] 
    point[2] [  0.11  -0.08  ] 
    point[3] [  0.11   0.08  ] 
    point[4] [  0.095  0.135 ] 
    point[5] [ -0.185  0.135 ]
    point[6] [ -0.215  0.1   ]
    point[7] [ -0.215 -0.1   ] 
    z [ 0.059 0.234 ]
  )

  # sonar case
  block
  (
    points 9
    point[0]  [ -0.135  0.136 ]
    point[1]  [ -0.185  0.136 ]
    point[2]  [ -0.223  0.101 ]
    point[3]  [ -0.248  0.054 ]
    point[4]  [ -0.258  0     ]
    point[5]  [ -0.248 -0.054 ]
    point[6]  [ -0.223 -0.101 ]
    point[7]  [ -0.185 -0.136 ]
    point[8]  [ -0.135 -0.136 ]
    z [ 0.184 0.234 ]
  )

  # sonar case
  block
  (
    points 9
    point[0]  [ 0.046 -0.136 ]
    point[1]  [ 0.096 -0.136 ]
    point[2]  [ 0.134 -0.101 ]
    point[3]  [ 0.159 -0.054 ]
    point[4]  [ 0.168  0     ]
    point[5]  [ 0.159  0.054 ]
    point[6]  [ 0.134  0.101 ]
    point[7]  [ 0.096  0.136 ]
    point[8]  [ 0.046  0.136 ]
    z [ 0.184 0.234 ]
  )
  
  # left wheel
  block
  (
    points 4
    point[0] [  0.083  0.177 ]
    point[1] [ -0.083  0.177 ]
    point[2] [ -0.083  0.140 ]
    point[3] [  0.083  0.140 ]
    z [0 0.165 ]
    color "gray15"
  )

  # right wheel
  block
  (
    points 4
    point[0] [  0.083  -0.14 ]
    point[1] [ -0.083  -0.14 ]
    point[2] [ -0.083  -0.177 ]
    point[3] [  0.083  -0.177 ]
    z [ 0 0.165 ]
    color "gray15"
  )

  # castor
  block
  (
    points 4
    point[3] [ -0.2475  0.012 ]
    point[2] [ -0.1825  0.012 ]
    point[1] [ -0.1825 -0.012 ]
    point[0] [ -0.2475 -0.012 ]
    z [ 0 0.065 ]
    color "gray15"
  )
 
  # lid
  block
  (
    points 22
    point[21] [  0.174 0 ]
    point[20] [  0.166 -0.056 ]
    point[19] [  0.145 -0.107 ]
    point[18] [  0.112 -0.155 ]
    point[17] [  0.064 -0.190 ]
    point[16] [  -0.074 -0.190 ]
    point[15] [  -0.096 -0.160 ]
    point[14] [  -0.151 -0.160 ]
    point[13] [  -0.2   -0.155 ]
    point[12] [  -0.236 -0.107 ]
    point[11] [  -0.256 -0.056 ]
    point[10] [  -0.264  0     ]
    point[9] [  -0.256  0.056 ]
    point[8] [ -0.236  0.107 ]
    point[7] [ -0.2    0.155 ]
    point[6] [ -0.151  0.160 ]
    point[5] [ -0.096  0.160 ]
    point[4] [ -0.074  0.190 ]
    point[3] [  0.064  0.190 ]
    point[2] [  0.112  0.155 ]
    point[1] [  0.145  0.107 ]
    point[0] [  0.166  0.056 ]
    z [ 0.234 0.24 ]

    # a dark top looks more realistic, but isn't very useful 
    # for a top-down view
    #color "gray10"
  )
)


# define 10 straight bumpers around the edge of the robot
#
# (these angles are correct for p2dx but the offsets are approximate - RTV)
# format: bumper[x] [x y th length radius] (zero radius gives a straight line)
# WARNING: bumpers are not currently supported by Stage>=1.5
# define pioneer2dxbumper bumper
# ( 
#   bumpers10
#   bumper[0] [  0.17 -0.22  -52  0.105 0.0 ]
#   bumper[1] [  0.24 -0.12  -19  0.105 0.0 ]
#   bumper[2] [  0.26  0.00    0  0.105 0.0 ]
#   bumper[3] [  0.24  0.12   19  0.105 0.0 ]
#   bumper[4] [  0.17  0.22   52  0.105 0.0 ]
#   bumper[5] [ -0.25  0.22  128  0.105 0.0 ]
#   bumper[6] [ -0.32  0.12  161  0.105 0.0 ]
#   bumper[7] [ -0.34  0.00  180  0.105 0.0 ]
#   bumper[8] [ -0.32 -0.12  199  0.105 0.0 ]
#   bumper[9] [ -0.25 -0.22  232  0.105 0.0 ]
# )


# The Pioneer3DX standard configuration
define pioneer3dx pioneer_base
(
  # Actual size
  size [0.511 0.4 0.22 ]

  # The pioneer's center of rotation is offset from its center of area
  origin [-0.04465 0.0 0.0]

  # Estimated mass in KG
  mass 23.0 

  # Body shape:
  block( 
    points 8
    point[0] [-0.2 0.12]
    point[1] [-0.2 -0.12]
    point[2] [-0.12 -0.2555]
    point[3] [0.12 -0.2555]
    point[4] [0.2 -0.12]
    point[5] [0.2 0.12]
    point[6] [0.12 0.2555]
    point[7] [-0.12 0.2555]
    z [0 0.22]
  )

  # Use the sonar array defined above
  p3dx_sonar( pose [ 0 0 -0.03 0 ] )  
) 

# The Pioneer3AT standard configuration
define pioneer3at pioneer_base
(
  # Actual size
  size [0.626 0.505]

  # The pioneer's center of rotation is offset from its center of area
  origin [-0.04465 0.0 0.0]

  # Estimated mass in KG
  mass 40.0 

  # Body shape:
  block( 
    points 8
    point[0] [-0.18 0.313]
    point[1] [0.18 0.313]
    point[2] [0.2525 0.18]
    point[3] [0.2525 -0.18]
    point[4] [0.18 -0.313]
    point[5] [-0.18 -0.313]
    point[6] [-0.2525 -0.18]
    point[7] [-0.2525 0.18]
  )

  # Use the sonar array defined above
  p3at_sonar( pose [ 0 0 -0.03 0 ] )  
)


### AMIGOBOT ####

# The AmigoBot sonar array
define amigo_sonar ranger
(
  scount 8
  spose[0] [ 0.073 0.105 90 ]
  spose[1] [ 0.130 0.078 41 ]
  spose[2] [ 0.154 0.030 15 ]
  spose[3] [ 0.154 -0.030 -15 ]
  spose[4] [ 0.130 -0.078 -41 ]	
  spose[5] [ 0.073 -0.105 -90 ]
  spose[6] [ -0.146 -0.060 -145 ]
  spose[7] [ -0.146 0.060 145 ]
)

define amigobot position
(
  size [0.330 0.280 0.25]
  origin [0 0 0 0] # what should this value be? send email to vaughan@sfu.ca.
  amigo_sonar( pose [0 0 -0.02 0 ] )
)
