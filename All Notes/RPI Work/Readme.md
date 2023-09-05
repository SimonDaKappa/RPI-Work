# This folder should contain all school notes and work I have completed.

## Todo 
1. Synchronize notability
	1. How to do?
	2.  Approach 1
		1.  Change notability backup from dropbox to some other service that can be accessed from both PC and iPad (Maybe learn to host a webserver?)
		2.  Script that automatically pulls all files from backup location and uploads to revision control (either current git, or automatic synchro for 8$ monthly). Possibly a callback to some service I create (would have to be on my webserver then) that pushes to origin when change to storage (eg notability updating a pdf)
		3. Custom obsidian startup script w/ git pull on startup to synchronize 
2. Notability visualization of synchronization diagram
	1. Mobile and PC
3.  Tags vs folders 

## Notability Auto-Backup

### iCloud
Notability automatically syncs files between all instances with same account using iCloud. As I have 50gb on iCloud, but only 2 on dropbox, it would be best to migrate. 

Once migrated, implementing an asynchronous app is next. 
This app should do the following
	Periodically poll iCloud for new files to save to origin git repo
	Pull these changes from github into working copy / local instance
	Add these changes to obsidian 
	Sync should do the rest

I think a plugin should handle this on the PC side, so that it can be bootstrapped into obsidian open, close, and maybe keybinds later.

Assigning notability pdfs to the correct tag will take a large amount of manual work. Right now, it seems that including them in the title would be the easiest way, but I had like 540 notes at this point. Then plugin can parse names for tags 
