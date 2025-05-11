
        return linearProbing(oldHash, (newHash+1) % 5, username);
    }
    return -1;
}

int existingUser(string username, int hash){
    if (users[hash][0] == username)
    {