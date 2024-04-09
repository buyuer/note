class Obj(object):
    def __getitem__(self, key):
        print(key)
        return 123


def main():
    obj = Obj()
    print(obj['test'])


if __name__ == '__main__':
    main()
