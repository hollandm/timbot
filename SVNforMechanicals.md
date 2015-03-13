# Introduction #

Basic Terminology:
  * Repository: 	The remote location of CAD, Code, and other files.
  * Check out:	To make a local copy of the repository.
  * Commit:	To upload, update, or otherwise change a file or folder to the repository.
  * Update:	Pull any commits made by others to the repository, and apply those to your local copy.


# Details #

  1. Download and Install TortoiseSVN from http://tortoisesvn.net/
  1. Once TortoiseSVN is installed, right click in the directory where you want to check out the repository, and click SVN Checkout
> > ![https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN1.png](https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN1.png)
  1. Enter the url https://timbot.googlecode.com/svn/trunk/ in the “URL of repository field”, and hit OK.
> > ![https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN2.png](https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN2.png)
  1. TortoiseSVN will then download all the files in the repository, and create a folder on your desktop named “timbot”. This folder is where you will put all of your files.
> > ![https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN3.png](https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN3.png)
> > ![https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN4.png](https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN4.png)
  1. To update this, all I have to do is right click the directory, and select SVN update. TortoiseSVN will take care of the rest.
  1. Let’s say I want to add a new file. Once created, you’ll note that is doesn’t have the green check mark by it, indicated it is not being tracked, or watched by TortoiseSVN. To add it to the tracked list, and therefore add it to the repository, you need to right click on the file, and select “TortoiseSVN->Add”.
> > ![https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN5.png](https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN5.png)
> > ![https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN6.png](https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN6.png)
> > ![https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN7.png](https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN7.png)
  1. Now, this has just added the file locally. We now need to _commit_ it, so that others can see it and download it. Right click once again in the directory, and then click "SVN Commit". This starts the commit process. You will receive a prompt, telling you what you changed, and giving you the option to add a comment on the change. **Make sure to add a comment to every commit, and make the comment very descriptive of what you've done.** On the first try, you will receive a login prompt. This requires your email (the personal gmail one), and a password you can get from https://code.google.com/hosting/settings.
> > ![https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN8.png](https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN8.png)
> > ![https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN9.png](https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN9.png)
> > ![https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN10.png](https://timbot.googlecode.com/svn/wiki/SVNIntro/SVN10.png)

That's all you need for a basic intro. And **Make sure you update before you start working**.