# ALICE_Hyper_work

## github items 
### first time pull the repository(using ssh not https)
1. create ssh key
cd ~/.ssh 
ls
// if there is no id_rsa.pub, then create it using 
ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
vim id_rsa.pub 
// copy the key and paste it to your github account
2. init the repository in your computer and gitpull
cd workingdir/
git init
git add README.md //choosable 
git add . // add all files
git add <file> //add a certain file
git commit -m "first commit" //""is the message
git remote add origin git@github.com:yourname/yourrepo.git
git push -u origin main //becarful of the branch name
### second time pull the repository
1. check the branch 
git branch
git checkout main //main branch
2. check out the file status
git status
3. add file to Standing Area
git add. //add all files
git add <file> //add a certain file
4. commit the file
git commit -m "second commit" 
5. pull the latest code form remote repository before pushing
git pull origin main
6. push the file to the github
git push origin main 